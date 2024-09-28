/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:45:16 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 18:04:12 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

bool	finished_by_meta(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (((len >= 2 && str[len - 2] == str[len - 1])
			|| (str[len - 1] != '&'))
		&& is_meta(str[len - 1]));
}

bool	is_brace_well_formatted(char *str)
{
	int		in_sq;
	int		in_dq;
	int		b_count;
	size_t	i;

	in_dq = 0;
	in_sq = 0;
	b_count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			in_sq = !in_sq;
		else if (str[i] == '"')
			in_dq = !in_dq;
		if (!in_sq || in_dq)
		{
			b_count += (str[i] == '$' && str[i + 1] == '{');
			if (str[i] == '}')
				b_count--;
			if (b_count < 0)
				return (false);
		}
	}
	return (!b_count);
}

bool	has_semicolon(char *str)
{
	int		in_sq;
	int		in_dq;
	size_t	i;

	in_sq = 0;
	in_dq = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (str[i] == '"' && !in_sq)
			in_dq = !in_dq;
		else if (str[i] == ';' && !in_sq && !in_dq)
			return (true);
		i++;
	}
	return (false);
}

int	is_well_formatted(char *str)
{
	int		p_count;
	int		in_sq;
	int		in_dq;
	size_t	i;

	p_count = 0;
	in_sq = 0;
	in_dq = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (str[i] == '"' && !in_sq)
			in_dq = !in_dq;
		else if (str[i] == '(' && !in_sq && !in_dq)
			p_count++;
		else if (str[i] == ')' && !in_sq && !in_dq)
		{
			p_count--;
			if (p_count < 0)
				return (-1);
		}
	}
	return (!p_count && !in_sq && !in_dq);
}
