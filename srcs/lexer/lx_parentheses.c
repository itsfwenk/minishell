/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_parentheses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:18:42 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/29 12:26:40 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

void	to_close_parenthesis(char *str, int *i)
{
	int	open_parentheses;

	i[1] = i[0];
	open_parentheses = 1;
	while (open_parentheses != 0)
	{
		i[1] = i[1] + 1;
		if (str[i[1]] == '(')
			open_parentheses++;
		if (str[i[1]] == ')')
			open_parentheses--;
	}
}

char	*trim_parentheses(char *str, int *i)
{
	char	*trimmed;

	trimmed = ft_calloc(i[1] - i[0], sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	ft_strlcpy(trimmed, &str[i[0] + 1], (i[1] - i[0]));
	return (trimmed);
}
