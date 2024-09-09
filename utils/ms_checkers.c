/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:27:17 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/03 13:56:23 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	finished_by_meta(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && str[len - 2] == str[len - 1]
		&& in_charset(str[len - 1], METAS))
		return (TRUE);
	return (str[len - 1] != '&' && in_charset(str[len - 1], METAS));
}

int	is_brace_well_formated(char *str)
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
				return (0);
		}
	}
	return (!b_count);
}

int	has_semicolon(char *str)
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
			return (1);
		i++;
	}
	return (0);
}

int	is_well_formated(char *str)
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
