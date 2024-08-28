/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:27:17 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/28 16:27:37 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
