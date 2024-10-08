/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_lst_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:10:09 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/07 11:50:54 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

bool	is_word_delimiter(t_token **tokens, char *str, int *i)
{
	int	char_type;

	if (str[i[0] + 1] && str[i[1]] && str[i[0] + 1] == '{' && str[i[1]] != '}')
		return (false);
	if (str[i[1]] == ' ' || str[i[1]] == '\t' || str[i[1]] == '\0')
		return (true);
	char_type = which_token(tokens, &str[i[1]]);
	if (char_type >= PIPE && char_type <= HERE_DOC)
		return (true);
	else
		return (false);
}

bool	lx_createadd(t_skibidi *shell, t_token **tokens, char *input, int *i)
{
	t_token	*ntoken;
	int		token_type;

	token_type = which_token(tokens, &input[i[0]]);
	if (token_type >= PIPE && token_type <= HERE_DOC)
		ntoken = lx_meta_token(shell, input, i, token_type);
	else
		ntoken = lx_str_token(shell, input, i, token_type);
	if (ntoken == NULL)
		exit_shell(shell);
	lx_addback(tokens, ntoken);
	return (true);
}

t_token	*empty_cmd(t_skibidi *shell, t_token *token)
{
	t_token	*empty;
	t_token	*token_prev;

	token_prev = token->prev;
	empty = ft_calloc(1, sizeof(t_token));
	if (empty == NULL)
		exit_shell(shell);
	empty->type = STR;
	empty->prev = token_prev;
	empty->next = token;
	token->prev = empty;
	token_prev->next = empty;
	return (empty);
}
