/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:54:47 by fli               #+#    #+#             */
/*   Updated: 2024/08/20 00:08:58 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_sep(char *c)
{
	int		i;
	char	sep[12];

	ft_strlcpy(sep, "\"\'|&<>()\t ", 12);
	i = 0;
	while (sep[i] != '\0')
	{
		if (c[0] == sep[i])
			return (TRUE);
		i++;
	}
	if (c[0] == '$')
	{
		if (ft_isalpha(c[1]) != 0 || c[1] == '_')
			return (TRUE);
	}
	return (FALSE);
}

t_token	*ft_lexer(char *input)
{
	int	i;
	int	j;
	t_token	*tokens;

	i = 0;
	while (input[i] != '\0')
	{
		j = 0;
		while (is_sep(input[j]) == FALSE)
		{
			j++;
		}
		lx_createadd(&tokens, input, i, j);
	}

}
