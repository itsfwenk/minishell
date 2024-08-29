/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:08:07 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/28 16:03:01 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lexer(char *input)
{
	int		i[2];
	t_token	*tokens;

	if (input == NULL || input[0] == '\0')
		return (NULL);
	ft_bzero(i, 2 * sizeof(int));
	tokens = NULL;
	while (input[i[0]] != '\0')
	{
		while (input[i[0]] != '\0'
			&& (input[i[0]] == ' ' || input[i[0]] == '\t'))
		{
			i[0] = i[0] + 1;
		}
		if (i[0] >= (int)ft_strlen(input))
			break ;
		i[1] = i[0] + 1;
		if (lx_createadd(&tokens, input, i) == FALSE)
			return (NULL); // ft_exit_clean
		i[0] = i[1] + 1;
	}
	return (tokens);
}
