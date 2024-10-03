/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_redirs_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:53:26 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/03 19:21:38 by mel-habi         ###   ########.fr       */
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

void	check_for_here_doc(t_skibidi *shell, t_token *current)
{
	int		hd_return;

	while (current)
	{
		if (current->type == HERE_DOC && !current->here_doc)
		{
			signal(SIGINT, heredoc_sig);
			signal(SIGQUIT, SIG_IGN);
			g_signal.code = 0;
			hd_return = get_here_doc_content(shell, current);
			if (hd_return == -1)
				exit_shell(shell);
			else if (g_signal.code)
			{
				g_signal.heredoc_sigint = true;
				return ;
			}
		}
		current = current->next;
	}
}

bool	expd_wc_only_redir(t_skibidi *shell, t_token *token)
{
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

void	open_only_redir(t_skibidi *shell, t_token *token)
{
	int		fd;

	if (g_signal.heredoc_sigint)
		return ;
	while (token)
	{
		fd = get_fd(shell, token);
		close(fd);
		token = token->next;
	}
}
