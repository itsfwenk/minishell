/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 23:18:42 by fli               #+#    #+#             */
/*   Updated: 2024/08/20 14:32:40 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lx_newtoken(char *str, int i, int j)
{
	t_token	*ntoken;

	ntoken = malloc(sizeof(t_token));
	if (ntoken == NULL)
		return (NULL);
	ntoken->str = lx_strdup(str, i, j);
	if (ntoken->str == NULL)
	{
		free (ntoken);
		return (NULL); // ft_exit_clean
	}
	ntoken->type = NULL;
	ntoken->next = NULL;
	return (ntoken);
}

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

void	lx_createadd(t_token **tokens, char *str, int i, int j)
{
	t_token	*ntoken;

	ntoken = lx_newtoken(str, i, j);
	if (ntoken == NULL)
	{
		lx_deltokens(tokens);
		return ; // exit ?
	}
	lx_addback(tokens, ntoken);
}

void	lx_deltokens(t_token **tokens)
{
	t_token	*prev;
	t_token	*current;

	current = *tokens;
	while (current != NULL)
	{
		free(current->str);
		prev = current;
		current = current->next;
		free(prev);
	}
}
