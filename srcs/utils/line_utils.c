/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:50:14 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 15:53:16 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

char	*trim_line(char *line)
{
	char	*trmimmed;

	trmimmed = ft_strtrim(line, " \t");
	free(line);
	return (trmimmed);
}

bool	check_line(char *line)
{
	int	well_formatted;

	well_formatted = is_well_formatted(line);
	if (well_formatted == -1)
	{
		ft_print_error(NULL, ")", \
					"syntax error near unexpected token", "`'");
		return (false);
	}
	else if (finished_by_meta(line) || !is_brace_well_formatted(line)
		|| has_semicolon(line) || !well_formatted)
	{
		ft_print_error("check_line", NULL, \
			"there's at least one error in the line you've just written...", \
			NULL);
		return (false);
	}
	return (true);
}
