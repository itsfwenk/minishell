/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_lst_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:28:57 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/16 18:56:36 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	lx_createadd(t_token **tokens, t_skibidi *skibidishell, char *input, int *i)
{
	t_token	*ntoken;
	int		token_type;

	token_type = which_token(tokens, &input[i[0]]);
	if (token_type >= PIPE && token_type <= HERE_DOC)
		ntoken = lx_meta_token(input, i, token_type, skibidishell);
	else
		ntoken = lx_str_token(skibidishell, input, i, token_type);
	if (ntoken == NULL)
		ft_free_clean(skibidishell);
	lx_addback(tokens, ntoken);
	return (TRUE);
}
