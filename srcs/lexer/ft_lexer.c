/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:03:23 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/03 19:21:13 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

void	check_for_heredoc(t_skibidi *shell, t_token *token)
{
	t_token	*redir;

	redir = token->redir;
	while (redir)
	{
		if (redir->type == HERE_DOC)
		{
			signal(SIGINT, heredoc_sig);
			signal(SIGQUIT, SIG_IGN);
			g_signal.code = 0;
			redir->fd = get_here_doc_content(shell, redir);
			if (redir->fd == -1)
				exit_shell(shell);
			else if (g_signal.code)
			{
				g_signal.heredoc_sigint = true;
				return ;
			}
		}
		redir = redir->next;
	}
}

t_token	*ft_lexer(t_skibidi *shell, char *input)
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
			i[0] = i[0] + 1;
		if (i[0] >= (int)ft_strlen(input))
			break ;
		i[1] = i[0] + 1;
		if (lx_createadd(shell, &tokens, input, i) == false)
			return (NULL);
	}
	return (tokens);
}

void	merge_operators(t_skibidi *shell, t_token *current)
{
	t_token	*next_cmd;

	if (current && (current->type == PIPE || current->type == OR
			|| current->type == AND))
	{
		next_cmd = get_cmd(current);
		merge_tokens(shell, &current->next, NULL);
		current->next = next_cmd;
	}
}

void	merge_tokens(t_skibidi *shell, t_token **token, t_token *cmd)
{
	t_token	*current;

	current = NULL;
	if (!token || *token == NULL || only_redirs(*token))
		return ;
	if (*token && (*token)->type == PAR_STR)
	{
		merge_tokens(shell, &(*token)->next, *token);
		merge_tokens(shell, &(*token)->sub_shell, NULL);
	}
	current = *token;
	if (cmd == NULL)
		cmd = get_cmd(*token);
	if (current == cmd)
		current = current->next;
	merge_operators(shell, current);
	merge_redirection(shell, current, cmd);
	merge_arguments(shell, current, cmd);
	if (shell->tokens->type != PAR_STR && cmd != NULL && cmd->type != PAR_STR)
		shell->tokens = cmd;
}
