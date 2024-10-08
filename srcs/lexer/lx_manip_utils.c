/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_manip_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:17:30 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/07 10:41:20 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

char	*lx_strictstrdup(char *str, int *i)
{
	int		j;
	int		start;
	int		end;
	int		truelen;
	char	*dup;

	truelen = i[1] - i[0] + 1;
	dup = ft_calloc(truelen + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	start = i[0];
	end = start + truelen;
	j = 0;
	while (start < end)
	{
		dup[j] = str[start];
		j++;
		start++;
	}
	dup[truelen] = '\0';
	return (dup);
}

char	*lx_strdup(char *str, int *i)
{
	int		j;
	int		start;
	int		end;
	int		truelen;
	char	*dup;

	truelen = i[1] - i[0] + 1;
	if (str[i[0]] == '\'' || str[i[0]] == '"')
		truelen = i[1] - i[0] - 1;
	dup = ft_calloc(truelen + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	start = i[0];
	if (str[i[0]] == '\'' || str[i[0]] == '"')
		start = i[0] + 1;
	end = start + truelen;
	j = 0;
	while (start < end)
	{
		dup[j] = str[start];
		j++;
		start++;
	}
	dup[truelen] = '\0';
	return (dup);
}

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
	{
		last->next = ntoken;
		ntoken->prev = last;
	}
}

void	lx_deltokens(t_token **tokens)
{
	t_token	*prev;
	t_token	*current;

	current = *tokens;
	while (current != NULL)
	{
		if (current->assembled)
			free(current->assembled);
		if (current->full_string)
			free(current->full_string);
		if (current->argv)
			free_str_tab(current->argv);
		tstring_del(&current->tstring);
		tstring_del(&current->wildcard_list);
		if (current->pid)
			free(current->pid);
		lx_deltokens(&current->arguments);
		lx_deltokens(&current->redir);
		lx_deltokens(&current->sub_shell);
		free_tpipe(current->garbage_pipe);
		prev = current;
		current = current->next;
		free(prev);
	}
	*tokens = NULL;
}
