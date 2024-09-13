/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:08:07 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/13 18:25:50 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	merge_redirection(t_skibidi *skibidishell, t_token *current, t_token *cmd)
{
	t_token	*new_start;

	if (current && (current->type == IN_REDIR || current->type == HERE_DOC))
	{
		lx_addback(&(cmd->infile), current);
		new_start = current->next->next;
		if (new_start == cmd)
			new_start = cmd->next;
		current->next->next = NULL;
		merge_tokens(skibidishell, &new_start, cmd);
	}
	if (current && (current->type == OUT_REDIR
			|| current->type == APD_OUT_REDIR))
	{
		lx_addback(&(cmd->outfile), current);
		new_start = current->next->next;
		if (new_start == cmd)
			new_start = cmd->next;
		current->next->next = NULL;
		merge_tokens(skibidishell, &new_start, cmd);
	}
}

static void	merge_arguments(t_skibidi *skibidishell, t_token *current, t_token *cmd)
{
	t_token	*new_start;

	if (current && cmd && current->type == STR)
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
		if (current->type == STR)
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

	current = NULL;
	if (!token || *token == NULL)
		return ;
	if (*token && (*token)->type == PAR_STR)
	{
		merge_tokens(skibidishell, &(*token)->next, NULL);
		merge_tokens(skibidishell, &(*token)->sub_shell, NULL);
	}
	current = *token;
	if (cmd == NULL)
		cmd = get_cmd(*token);
	if (current == cmd)
		current = current->next;
	if (token && ((*token)->type == PIPE || (*token)->type == OR
			|| (*token)->type == AND))
		merge_tokens(skibidishell, &current->next, NULL);
	merge_redirection(skibidishell, current, cmd);
	merge_arguments(skibidishell, current, cmd);
	if (skibidishell->tokens->type != PAR_STR)
		skibidishell->tokens = cmd;
}
