/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:54:47 by fli               #+#    #+#             */
/*   Updated: 2024/08/22 19:55:11 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lexer(char *input)
{
	int	i[2];
	t_token	*tokens;

	ft_bzero(i, 2);
	while (input[i[0]] != '\0')
	{
			while (input[0] == ' ' || input[0] == '\t')
			{
				i[0] = i[0] + 1;
			}
			lx_createadd(&tokens, input, i);
			i[0] = i[1];
	}
		// lx_createadd(&tokens, input, i, j);
		// j++;
		// while (input[j] == ' ' || input[j] == '\t')
		// {
		// 	j++;
		// }
}

