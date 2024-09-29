/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:03:23 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/29 10:20:37 by mel-habi         ###   ########.fr       */
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
			redir->fd = get_here_doc_content(shell, redir);
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

void	merge_tokens(t_skibidi *shell, t_token **token, t_token *cmd)
{
	t_token	*current;

	current = NULL;
	if (!token || *token == NULL)
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
