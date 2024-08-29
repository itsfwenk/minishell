/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_parentheses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:56:29 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/28 14:56:39 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	trimmed = malloc((i[1] - i[0]) * sizeof(char));
	if (trimmed == NULL)
		return (NULL); // ft_exit_clean
	ft_strlcpy(trimmed, &str[i[0] + 1], (i[1] - i[0]));
	printf("trim parentheses : %s\n", trimmed);
	return (trimmed);
}
