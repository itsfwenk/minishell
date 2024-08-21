/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:44:09 by fli               #+#    #+#             */
/*   Updated: 2024/08/21 18:29:37 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	lx_createadd_str(t_token **tokens, char *str, int i, int j)
// {
// 	t_token	*ntoken;

// 	ntoken = lx_newtoken(str, i, j);
// 	if (ntoken == NULL)
// 	{
// 		lx_deltokens(tokens);
// 		return ; // exit ?
// 	}
// 	lx_addback(tokens, ntoken);
// }

static int	is_word_delimiter(char *str, int i)
{
	int	char_type;

	if (str[i] == ' ' || str[i] == '\t')
		return (TRUE);
	char_type = which_sep(&str[i]);
	if (char_type >= PIPE && char_type <= HERE_DOC)
		return (TRUE);
	else
		return (FALSE);
}

void	lx_createadd(t_token **tokens, char *str, int i, int *j)
{
	t_token	*ntoken;
	int		token_type;

	token_type = which_sep(&str[1]);
	if (token_type >= D_QUOTE && token_type <= CLS_PAR)
		(*j) = (*j) + 1;
	else if (token_type >= OR && token_type <= HERE_DOC)
		(*j) = (*j) + 2;
	else
	{
		while (is_word_delimiter(str, *j) == FALSE)
		{
			(*j)++;
		}
		//
	}
	ntoken = lx_newtoken(str, i, *j, token_type);
	if (ntoken == NULL)
	{
		lx_deltokens(tokens);
		return ; // exit ?
	}
	lx_addback(tokens, ntoken);
}
