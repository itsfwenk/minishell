/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:54:47 by fli               #+#    #+#             */
/*   Updated: 2024/08/26 17:22:38 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lexer(char *input)
{
	int		i[2];
	t_token	*tokens;

	if (input == NULL || input[0] == '\0')
		return (NULL);
	ft_bzero(i, 2);
	tokens = NULL;
	while (input[i[0]] != '\0')
	{
			while (input[i[0]] != '\0' &&
				(input[i[0]] == ' ' || input[i[0]] == '\t'))
			{
				i[0] = i[0] + 1;
			}
			i[1] = i[0] + 1;
			if (lx_createadd(&tokens, input, i) == FALSE)
				return (NULL); // ft_exit_clean
			i[0] = i[1];
	}
	return (tokens);
}

