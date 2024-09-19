/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:51:23 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/19 15:31:31 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	merge_redirection(t_skibidi *skibidishell,
	t_token *current, t_token *cmd)
{
	t_token	*new_start;
	t_token	*next_token;

	if (current && (current->type == IN_REDIR || current->type == HERE_DOC
			|| current->type == OUT_REDIR || current->type == APD_OUT_REDIR))
	{
		lx_addback(&(cmd->redir), current);
		new_start = current->next->next;
		current->next->next = NULL;
		if (new_start == cmd)
		{
			if (new_start->next->type == IN_REDIR
				|| new_start->next->type == HERE_DOC
				|| new_start->next->type == OUT_REDIR
				|| new_start->next->type == APD_OUT_REDIR)
			{
				next_token = get_next_token(new_start->next);
				cmd->next = next_token;
				merge_redirection(skibidishell, new_start->next, cmd);
			}
		}
		if (new_start == NULL)
			cmd->next = NULL;
		merge_tokens(skibidishell, &new_start, cmd);
	}
}

void	merge_arguments(t_skibidi *skibidishell,
	t_token *current, t_token *cmd)
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
		merge_tokens(skibidishell, &new_start, cmd);
	}
}

t_token	*get_cmd(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->type == STR || current->type == PAR_STR)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	merge_operators(t_skibidi *skibidishell, t_token *current)
{
	t_token	*next_cmd;

	if (current && (current->type == PIPE || current->type == OR
			|| current->type == AND))
	{
		next_cmd = get_cmd(current);
		merge_tokens(skibidishell, &current->next, NULL);
		current->next = next_cmd;
	}
}
