/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_redirs_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:53:26 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/30 14:15:24 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

bool	only_redirs(t_token *token)
{
	while (token)
	{
		if (token->type == STR || token->type == PAR_STR)
			return (false);
		token = token->next;
	}
	return (true);
}

void	check_for_here_doc(t_skibidi *shell)
{
	int		hd_return;
	t_token	*current;

	current = shell->tokens;
	while (current)
	{
		if (current->type == HERE_DOC)
		{
			signal(SIGINT, heredoc_sig);
			hd_return = get_here_doc_content(shell, current);
			if (hd_return == -1)
				exit_shell(shell);
		}
		current = current->next;
	}
}

bool	expd_wc_only_redir(t_skibidi *shell)
{
	t_token	*token;

	token = shell->tokens;
	while (token)
	{
		if (token->type != HD_LIMITER)
		{
			if (ft_expander(shell, token) == false)
				return (false);
		}
		assemble_tstring(shell, token);
		get_filenames(shell, token);
		token = token->next;
	}
	return (true);
}

void	open_only_redir(t_skibidi *shell)
{
	int		fd;
	t_token	*token;

	token = shell->tokens;
	if (g_signal)
		return ;
	while (token)
	{
		fd = get_fd(shell, token);
		close(fd);
		token = token->next;
	}
}
