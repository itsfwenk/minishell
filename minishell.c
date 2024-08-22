/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:50:41 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/22 17:05:38 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	handle_line(char *line, t_env **env)
{
	char	**splitted;

	splitted = ft_split(line, " \t");
	if (!splitted)
		g_signal = 1;
	else
	{
		if (!ft_strcmp("cd", splitted[0]))
			g_signal = ft_cd(splitted[1]);
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

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*line;

	(void)argc;
	(void)argv;
	env = NULL;
	if (ft_export(&env, envp))
		return (2);
	line = readline(ft_get_prompt(g_signal));
	while (line)
	{
		if (line[0])
		{
			add_history(line);
			handle_line(line, &env);
		}
		free(line);
		line = readline(ft_get_prompt(g_signal));
	}
	clear_history();
	free_env(env);
	return (0);
}
