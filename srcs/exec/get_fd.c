/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:25:21 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/29 12:05:49 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

int	get_hd_fd(t_skibidi *shell, t_token *redirection)
{
	int		fd_redir;
	char	*heredoc_num;
	char	*heredoc_name;

	heredoc_num = ft_itoa(redirection->here_doc);
	if (heredoc_num == NULL)
		exit_shell(shell);
	heredoc_name = ft_strjoin(".here_doc", heredoc_num);
	if (heredoc_name == NULL)
	{
		free(heredoc_num);
		exit_shell(shell);
	}
	fd_redir = open(heredoc_name, O_RDONLY);
	free(heredoc_num);
	free(heredoc_name);
	return (fd_redir);
}

int	get_fd(t_skibidi *shell, t_token *redirection)
{
	int		fd_redir;

	fd_redir = -1;
	if (redirection->type == IN_REDIR)
		fd_redir = open(redirection->next->assembled, O_RDONLY);
	if (redirection->type == HERE_DOC)
		fd_redir = get_hd_fd(shell, redirection);
	if (redirection->type == OUT_REDIR)
		fd_redir = open(redirection->next->assembled,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirection->type == APD_OUT_REDIR)
		fd_redir = open(redirection->next->assembled,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	redirection->fd = fd_redir;
	return (fd_redir);
}
