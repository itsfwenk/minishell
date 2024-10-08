/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:38:25 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/05 11:09:21 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	unlink_file(t_skibidi *shell, t_token *redir)
{
	char	*heredoc_num;
	char	*heredoc_name;

	heredoc_num = ft_itoa(redir->here_doc);
	if (heredoc_num == NULL)
		exit_shell(shell);
	heredoc_name = ft_strjoin(".here_doc", heredoc_num);
	if (heredoc_name == NULL)
	{
		free(heredoc_num);
		exit_shell(shell);
	}
	unlink(heredoc_name);
	free(heredoc_num);
	free(heredoc_name);
}

void	unlink_heredoc(t_skibidi *shell, t_token *token)
{
	t_token	*redir;

	while (token)
	{
		if (token->type == PAR_STR)
			unlink_heredoc(shell, token->sub_shell);
		else if (token->type == HERE_DOC)
			unlink_file(shell, token);
		redir = token->redir;
		while (redir)
		{
			if (redir->type == HERE_DOC)
				unlink_file(shell, redir);
			redir = redir->next;
		}
		token = token->next;
	}
	dup2(shell->stdin_save, STDIN_FILENO);
	dup2(shell->stdout_save, STDOUT_FILENO);
	close(shell->stdin_save);
	close(shell->stdout_save);
}
