/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:24:02 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 18:32:51 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static bool	dup_fd(int fd_redir, t_token *redirection)
{
	int		dup_return;

	if (redirection->type == IN_REDIR || redirection->type == HERE_DOC)
		dup_return = dup2(fd_redir, STDIN_FILENO);
	if (redirection->type == OUT_REDIR || redirection->type == APD_OUT_REDIR)
		dup_return = dup2(fd_redir, STDOUT_FILENO);
	if (dup_return == -1)
	{
		close(fd_redir);
		return (false);
	}
	close(fd_redir);
	return (true);
}

static bool	side_fd_manager(t_skibidi *shell, int *pipetab, t_side side)
{
	if (pipetab != NULL && side == LEFT)
	{
		if (dup2(pipetab[1], STDOUT_FILENO) == -1)
			return (close_pipe(pipetab), exit_shell(shell), false);
		close_pipe(pipetab);
	}
	if (pipetab != NULL && side == RIGHT)
	{
		if (dup2(pipetab[0], STDIN_FILENO) == -1)
			return (close_pipe(pipetab), exit_shell(shell), false);
		close_pipe(pipetab);
	}
}

static bool	previous_pipe_manager(t_skibidi *shell, t_token *tree, t_side side)
{
	if (tree->previous_pipe != NULL && side == LEFT)
	{
		if (dup2(tree->previous_pipe[0], STDIN_FILENO) == -1)
			return (close_pipe(tree->previous_pipe), false);
		close_pipe(tree->previous_pipe);
	}
	if (tree->previous_pipe != NULL && side == RIGHT)
	{
		if (dup2(tree->previous_pipe[1], STDOUT_FILENO) == -1)
			return (close_pipe(tree->previous_pipe), false);
		close_pipe(tree->previous_pipe);
	}
}

void	close_pipe(int pipefd[2])
{
	if (pipefd == NULL)
		return ;
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	pipefd[0] = -1;
	pipefd[1] = -1;
}

int	fd_manager(t_skibidi *shell, t_token *tree,
	int *pipetab, t_side side)
{
	int		fd_redir;
	t_token	*redirection;

	fd_redir = -1;
	redirection = tree->redir;
	while (redirection != NULL)
	{
		fd_redir = get_fd(redirection, shell);
		if (fd_redir == -1)
			return (false);
		if (dup_fd(fd_redir, redirection) == false)
			return (false);
		close(fd_redir);
		redirection = redirection->next->next;
	}
	side_fd_manager(shell, pipetab, side);
	previous_pipe_manager(shell, tree, side);
	return (true);
}
