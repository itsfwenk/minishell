/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:23:58 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/07 13:07:59 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

t_token	*get_next_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->type == STR || current->type == PIPE
			|| current->type == OR || current->type == AND
			|| current->type == PAR_STR)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static void	redir_util(t_skibidi *shell, t_token *new_start,
	t_token *cmd, bool in_sub)
{
	t_token	*next_token;

	if (new_start->next && (new_start->next->type == IN_REDIR
			|| new_start->next->type == HERE_DOC
			|| new_start->next->type == OUT_REDIR
			|| new_start->next->type == APD_OUT_REDIR))
	{
		next_token = get_next_token(new_start->next);
		new_start = new_start->next;
		cmd->next = next_token;
		merge_redirection(shell, new_start, cmd, in_sub);
	}
}

void	merge_redirection(t_skibidi *shell, t_token *current,
	t_token *cmd, bool in_sub)
{
	t_token	*new_start;

	if (current && (current->type == IN_REDIR || current->type == HERE_DOC
			|| current->type == OUT_REDIR || current->type == APD_OUT_REDIR))
	{
		lx_addback(&(cmd->redir), current);
		new_start = current->next->next;
		current->next->next = NULL;
		if (new_start == cmd)
			redir_util(shell, new_start, cmd, in_sub);
		if (new_start == NULL)
			cmd->next = NULL;
		merge_tokens(shell, &new_start, cmd, in_sub);
	}
}

void	merge_arguments(t_skibidi *shell,
	t_token *current, t_token *cmd, bool in_sub)
{
	t_token	*new_start;

	if (current && cmd && current != cmd && current->type == STR)
	{
		lx_addback(&(cmd->arguments), current);
		new_start = current->next;
		current->next = NULL;
		cmd->next = new_start;
		if (new_start)
			cmd->next = new_start;
		merge_tokens(shell, &new_start, cmd, in_sub);
	}
}

t_token	*get_cmd(t_skibidi *shell, t_token *token)
{
	t_token	*current;
	t_token	*empty;

	current = token;
	while (current != NULL)
	{
		if (current->type == STR || current->type == PAR_STR)
			return (current);
		if (current->type == PIPE || current->type == AND
			|| current->type == OR)
		{
			empty = empty_cmd(shell, current);
			return (empty);
		}
		current = current->next;
	}
	return (NULL);
}
