/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:54:47 by fli               #+#    #+#             */
/*   Updated: 2024/08/21 15:25:43 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lexer(char *input)
{
	int	i;
	int	j;
	t_token	*tokens;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
			lx_createadd_str(&tokens, input, i, &j);
			i = j;
	}
		// lx_createadd(&tokens, input, i, j);
		// j++;
		// while (input[j] == ' ' || input[j] == '\t')
		// {
		// 	j++;
		// }
}

