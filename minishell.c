/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:50:41 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/23 16:28:40 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static char	*join_line(char *full_line, char *line)
{
	char	*tmp;

	tmp = full_line;
	full_line = ft_strjoin(full_line, line);
	free(tmp);
	return (full_line);
}

static void	handle_line(char *line, t_env **env)
{
	char	**splitted;

	splitted = ft_split(line, " \t");
	if (!splitted)
		g_signal = 1;
	else
	{
		if (!ft_strcmp("cd", splitted[0]))
			g_signal = ft_cd(&splitted[1]);
		else if (!ft_strcmp("echo", splitted[0]))
			g_signal = ft_echo(&splitted[1]);
		else if (!ft_strcmp("env", splitted[0]))
			g_signal = ft_env(*env);
		else if (!ft_strcmp("exit", splitted[0]))
			g_signal = ft_exit(&splitted[1]);
		else if (!ft_strcmp("export", splitted[0]))
			g_signal = ft_export(env, &splitted[1]);
		else if (!ft_strcmp("pwd", splitted[0]))
			g_signal = ft_pwd();
		else if (!ft_strcmp("unset", splitted[0]))
			g_signal = ft_unset(*env, &splitted[1]);
		else
		{
			ft_print_error(splitted[0], NULL, "command not found", NULL);
			g_signal = 2;
		}
	}
	free_all(splitted);
}

static int	check_line(char **line)
{
	int		well_formated;
	char	*tmp;

	well_formated = is_well_formated(*line);
	while (well_formated <= 0)
	{
		if (well_formated == -1)
		{
			ft_print_error(NULL, ")", \
				"syntax error near unexpected token", "`'");
			return (2);
		}
		tmp = readline("> ");
		if (tmp)
		{
			*line = join_line(*line, tmp);
			free(tmp);
			if (!line)
				return (2);
		}
		well_formated = is_well_formated(*line);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*line;

	(void)argc;
	(void)argv;
	env = NULL;
	if (ft_export(&env, envp) || !reset_utils_env(&env))
		return (2);
	line = readline(ft_get_prompt(g_signal));
	while (line)
	{
		if (line[0])
		{
			g_signal = check_line(&line);
			if (g_signal != 2)
			{
				add_history(line);
				handle_line(line, &env);
			}
		}
		free(line);
		reset_utils_env(&env);
		line = readline(ft_get_prompt(g_signal));
	}
	return (rl_clear_history(), free_env(env), 0);
}
