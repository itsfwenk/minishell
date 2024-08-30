/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:50:41 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/30 17:48:39 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static char	*free_and_trim(char *str)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = str;
	str = ft_strtrim(str, " \t");
	free(tmp);
	return (str);
}

static char	*join_line(char *full_line, char *line)
{
	char	*tmp;
	char	*c;

	c = "\n";
	if (finished_by_meta(full_line) || (between_parentheses(full_line)
		&& !full_line[1]))
		c = " ";
	else if (between_parentheses(full_line))
		c = "; ";
	tmp = full_line;
	full_line = ft_strjoin(full_line, c);
	if (full_line)
	{
		free(tmp);
		tmp = full_line;
		full_line = ft_strjoin(full_line, line);
	}
	free(tmp);
	return (full_line);
}

static void	handle_line(char *line, t_skibidi *skibidishell)
{
	(void)skibidishell;
	(void)line;
	//main_lexer(line);
}

static int	check_line(char **line)
{
	int		well_formated;
	char	*tmp;

	if (!(*line)[0])
		return (0);
	well_formated = is_well_formated(*line) * !finished_by_meta(*line);
	while (well_formated <= 0)
	{
		if (well_formated == -1)
		{
			ft_print_error(NULL, ")", \
				"syntax error near unexpected token", "`'");
			return (2);
		}
		tmp = free_and_trim(readline("> "));
		if (tmp)
		{
			*line = join_line(*line, tmp);
			free(tmp);
			if (!line)
				return (2);
		}
		well_formated = is_well_formated(*line) * !finished_by_meta(*line);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_skibidi	*skibidishell;
	char		*line;

	(void)argv;
	(void)argc;
	skibidishell = ft_calloc(1, sizeof(t_skibidi));
	if (!skibidishell)
		return (2);
	if (!ft_export(&skibidishell->env, envp) && reset_utils_env(&skibidishell->env))
	{
		line = free_and_trim(readline(ft_get_prompt(g_signal)));
		while (line)
		{
			if (line[0])
			{
				g_signal = check_line(&line);
				if (g_signal != 2)
				{
					add_history(line);
					handle_line(line, skibidishell);
				}
			}
			free(line);
			reset_utils_env(&skibidishell->env);
			line = free_and_trim(readline(ft_get_prompt(g_signal)));
		}
	}
	rl_clear_history();
	ft_free_clean(skibidishell);
	return (0);
}
