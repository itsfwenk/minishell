/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:50:41 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/06 15:31:04 by mel-habi         ###   ########.fr       */
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
	str = ft_strtrim(str, " \t\n\v\f\r");
	free(tmp);
	return (str);
}

static void	handle_line(char *line, t_skibidi *skibidishell)
{
	(void)skibidishell;
	(void)line;
	//main_lexer(line);
}

static int	check_line(char *line)
{
	int	well_formated;

	well_formated = is_well_formated(line);
	if (well_formated == -1)
	{
		ft_print_error(NULL, ")", \
				"syntax error near unexpected token", "`'");
		return (2);	
	}
	else if (finished_by_meta(line) || !is_brace_well_formated(line)
		|| has_semicolon(line) || !well_formated)
	{
		ft_print_error("check_line", NULL, \
				"unexpected line", NULL);
		return (2);	
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
				g_signal = check_line(line);
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
