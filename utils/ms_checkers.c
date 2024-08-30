/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:27:17 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/30 17:52:00 by mel-habi         ###   ########.fr       */
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
	return (in_charset(str[len - 1], METAS));
}

int	between_parentheses(char *str)
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
				return (1);
		}
	}
	return (p_count);
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
