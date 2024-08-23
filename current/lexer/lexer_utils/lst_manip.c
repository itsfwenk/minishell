/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 23:18:42 by fli               #+#    #+#             */
/*   Updated: 2024/08/23 17:26:29 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*lx_meta_token(char *str, int *i, int token_type)
{
	t_token	*ntoken;

	ntoken = malloc(sizeof(t_token));
	if (ntoken == NULL)
		return (NULL); // ft_exit_clean
	if (token_type >= PIPE && token_type <= OUT_REDIR)
		i[1] = i[0] + 1;
	if (token_type >= OR && token_type <= HERE_DOC)
		i[1] = i[0] + 2;
	ntoken->value = lx_strdup(str, i, token_type);
	if (ntoken->value == NULL)
		return (NULL); // ft_exit_clean
	ntoken->to_be_expanded = FALSE;
	ntoken->type = token_type;
	ntoken->sub_shell = NULL;
	ntoken->next = NULL;
}

t_token	*lx_str_token(t_token **tokens, char *str, int *i, int token_type)
{
	t_token	*ntoken;

	ntoken = malloc(sizeof(t_token));
	if (ntoken == NULL)
		return (NULL); // ft_exit_clean
	while (is_word_delimiter(tokens, str, i[1]) == FALSE)
	{
		i[1] = i[1] + 1;
	}
	ntoken->value = lx_strdup(str, i, token_type);
	if (ntoken->value == NULL)
		return (NULL); // ft_exit_clean
	if (token_type == SQ_STR || token_type == HD_LIMITER)
		ntoken->to_be_expanded = FALSE;
	else
		ntoken->to_be_expanded = TRUE;
	ntoken->type = token_type;
	if (token_type == PAR_STR)
		ntoken->sub_shell = ft_lexer(ntoken->value); // subshell ft_lexer_subshell ? pre-process input to remove ()
	else
		ntoken->sub_shell = NULL;
	ntoken->next = NULL;
}

// t_token	*lx_newtoken(t_token **tokens, char *str, int *i, int token_type)
// {
// 	t_token	*ntoken;
// 	t_token	*last_token;

// 	ntoken = malloc(sizeof(t_token));
// 	if (ntoken == NULL)
// 		return (NULL); // ft_exit_clean
// 	ntoken->str = lx_strdup(str, i);
// 	if (ntoken->str == NULL)
// 	{
// 		free (ntoken);
// 		return (NULL); // ft_exit_clean
// 	}
// 	ntoken->type = token_type; // define type
// 	last_token = lx_getlast(*tokens);
// 	if (last_token != NULL && last_token->type == S_QUOTE)
// 		ntoken->to_be_expanded = FALSE;
// 	else
// 		ntoken->to_be_expanded = TRUE;
// 	ntoken->next = NULL;
// 	return (ntoken);
// }

t_token	*lx_getlast(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current == NULL)
		return (NULL);
	while (current != NULL)
	{
		current = current->next;
	}
	return (current);
}

void	lx_addback(t_token **tokens, t_token *ntoken)
{
	t_token	*last;

	last = lx_getlast(*tokens);
	if (last == NULL)
		*tokens = ntoken;
	else
		last->next = ntoken;
}

void	lx_deltokens(t_token **tokens)
{
	t_token	*prev;
	t_token	*current;

	current = *tokens;
	while (current != NULL)
	{
		free(current->value);
		prev = current;
		current = current->next;
		free(prev);
	}
}
