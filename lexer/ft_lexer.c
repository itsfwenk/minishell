/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:08:07 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/16 17:16:22 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_token *token)
{
	if (token && (token->type == IN_REDIR
		|| token->type == HERE_DOC
		|| token->type == OUT_REDIR
		|| token->type == APD_OUT_REDIR))
		return (TRUE);
	return (FALSE);
}

static t_token	*get_next_token(t_token *token)
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

static void	merge_redirection(t_skibidi *skibidishell, t_token *current, t_token *cmd)
{
	t_token	*new_start;
	t_token	*next_token;

	if (current && (current->type == IN_REDIR || current->type == HERE_DOC
		|| current->type == OUT_REDIR || current->type == APD_OUT_REDIR))
	{
		lx_addback(&(cmd->redir), current);
		new_start = current->next->next;
		if (new_start == cmd)
		{
			if (is_redir(new_start->next))
			{
				next_token = get_next_token(new_start->next);
				merge_redirection(skibidishell, new_start->next, cmd);
				cmd->next = next_token;
			}
		}
		if (new_start == NULL)
			cmd->next = NULL;
		current->next->next = NULL;
		merge_tokens(skibidishell, &new_start, cmd);
	}
}

static void	merge_arguments(t_skibidi *skibidishell, t_token *current, t_token *cmd)
{
	t_token	*new_start;

	if (current && cmd && current != cmd && current->type == STR)
	{
		lx_addback(&(cmd->arguments), current);
		new_start = current->next;
		current->next = NULL;
		cmd->next = NULL;
		if (new_start)
			cmd->next = new_start;
		merge_tokens(skibidishell, &new_start, cmd);
	}
}

static t_token	*get_cmd(t_token *token)
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

t_token	*ft_lexer(char *input)
{
	int		i[2];
	t_token	*tokens;

	if (input == NULL || input[0] == '\0')
		return (NULL);
	ft_bzero(i, 2 * sizeof(int));
	tokens = NULL;
	while (input[i[0]] != '\0')
	{
		while (input[i[0]] != '\0'
			&& (input[i[0]] == ' ' || input[i[0]] == '\t'))
		{
			i[0] = i[0] + 1;
		}
		if (i[0] >= (int)ft_strlen(input))
			break ;
		i[1] = i[0] + 1;
		if (lx_createadd(&tokens, input, i) == FALSE)
			return (NULL); // ft_exit_clean
		i[0] = i[1] + 1;
	}
	return (tokens);
}

void	merge_tokens(t_skibidi *skibidishell, t_token **token, t_token *cmd)
{
	t_token	*current;
	t_token	*next_cmd;

	current = NULL;
	if (!token || *token == NULL)
		return ;
	if (*token && (*token)->type == PAR_STR)
	{
		merge_tokens(skibidishell, &(*token)->next, *token);
		merge_tokens(skibidishell, &(*token)->sub_shell, NULL);
	}
	current = *token;
	if (cmd == NULL)
		cmd = get_cmd(*token);
	if (current == cmd)
		current = current->next;
	if (current && (current->type == PIPE || current->type == OR
			|| current->type == AND))
	{
		next_cmd = get_cmd(current);
		merge_tokens(skibidishell, &current->next, NULL);
		current->next = next_cmd;
	}
	merge_redirection(skibidishell, current, cmd);
	merge_arguments(skibidishell, current, cmd);
	if (skibidishell->tokens->type != PAR_STR && cmd != NULL)
		skibidishell->tokens = cmd;
}
