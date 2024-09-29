/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_redirs_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:53:26 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/29 12:30:25 by mel-habi         ###   ########.fr       */
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

void	expd_wc_only_redir(t_skibidi *shell)
{
	t_token	*token;

	token = shell->tokens;
	while (token)
	{
		if (token->type != HD_LIMITER)
			ft_expander(shell, token);
		assemble_tstring(shell, token);
		get_filenames(shell, token);
		token = token->next;
	}
}

void	open_only_redir(t_skibidi *shell)
{
	int		fd;
	t_token	*token;

	token = shell->tokens;
	while (token)
	{
		fd = get_fd(shell, token);
		close(fd);
		token = token->next;
	}
}
