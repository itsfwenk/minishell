/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_lst_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:28:57 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/13 12:56:43 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_word_delimiter(t_token **tokens, char *str, int i)
{
	int	char_type;

	if (str[i] == ' ' || str[i] == '\t' || str[i] == '\0')
		return (TRUE);
	char_type = which_token(tokens, &str[i]);
	if (char_type >= PIPE && char_type <= HERE_DOC)
		return (TRUE);
	else
		return (FALSE);
}

int	lx_createadd(t_token **tokens, char *input, int *i)
{
	t_token	*ntoken;
	int		token_type;

	token_type = which_token(tokens, &input[i[0]]);
	if (token_type >= PIPE && token_type <= HERE_DOC)
		ntoken = lx_meta_token(input, i, token_type);
	else
		ntoken = lx_str_token(tokens, input, i, token_type);
	if (ntoken == NULL)
	{
		lx_deltokens(tokens);
		return (FALSE); // exit ?
	}
	lx_addback(tokens, ntoken);
	return (TRUE);
}
