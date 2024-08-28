/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_lst_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 23:18:42 by fli               #+#    #+#             */
/*   Updated: 2024/08/28 13:20:09 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lx_meta_token(char *str, int *i, int token_type)
{
	t_token	*ntoken;

	ntoken = malloc(sizeof(t_token));
	if (ntoken == NULL)
		return (NULL); // ft_exit_clean
	if (token_type >= PIPE && token_type <= OUT_REDIR)
		i[1] = i[0];
	if (token_type >= OR && token_type <= HERE_DOC)
		i[1] = i[0] + 1;
	ntoken->tstring = malloc(sizeof(t_string));
	if (ntoken->tstring == NULL)
		return (NULL); // ft_exit_clean
	ntoken->tstring->str = lx_strdup(str, i);
	if (ntoken->tstring->str == NULL)
		return (NULL); // ft_exit_clean
	ntoken->tstring->to_be_expanded = FALSE;
	ntoken->tstring->between_quote = FALSE;
	ntoken->tstring->next = NULL;
	ntoken->type = token_type;
	ntoken->sub_shell = NULL;
	ntoken->next = NULL;
	return (ntoken);
}

t_token	*lx_str_token(t_token **tokens, char *str, int *i, int token_type)
{
	t_token	*ntoken;
	char	*trimmed_par;

	ntoken = malloc(sizeof(t_token));
	if (ntoken == NULL)
		return (NULL); // ft_exit_clean
	if (token_type == PAR_STR)
		to_close_parenthesis(str, i);
	else
	{
		while (is_word_delimiter(tokens, str, i[1]) == FALSE)
		{
			i[1] = i[1] + 1;
		}
		i[1] = i[1] - 1;
	}
	ntoken->tstring = create_tstring(tokens, str, i, token_type);
	if (ntoken->tstring == NULL)
		return (NULL); // ft_exit_clean
	ntoken->type = token_type;
	if (token_type == PAR_STR)
	{
		trimmed_par = trim_parentheses(str, i);
		if (trimmed_par == NULL)
			return (NULL); //ft_exit_clean
		ntoken->sub_shell = ft_lexer(trim_parentheses); // subshell ft_lexer_subshell ? pre-process input to remove ()
		free(trimmed_par);
	}
	else
		ntoken->sub_shell = NULL;
	ntoken->next = NULL;
	i[0] = i[1] + 1;
	return (ntoken);
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
	while (current->next != NULL)
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
		tstring_del(&current->tstring);
		if (current->sub_shell != NULL)
			lx_deltokens(&current->sub_shell);
		prev = current;
		current = current->next;
		free(prev);
	}
}
