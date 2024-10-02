/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:24:02 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/02 10:00:04 by fli              ###   ########.fr       */
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
	return (true);
}

static bool	previous_pipe_manager(t_token *tree, t_side side)
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
	return (true);
}

// void	close_pipe(int pipefd[2])
// {
// 	if (pipefd == NULL)
// 		return ;
// 	if (pipefd[0] != -1)
// 		close(pipefd[0]);
// 	if (pipefd[1] != -1)
// 		close(pipefd[1]);
// 	pipefd[0] = -1;
// 	pipefd[1] = -1;
// }

static bool	file_access_fail(t_skibidi *shell, t_token *redirection)
{
	shell->exit_code = EXIT_FAILURE;
	if (errno == EACCES)
		ft_print_error(redirection->next->assembled, NULL,
			"Permission denied", NULL);
	if (errno == ENOENT)
		ft_print_error(redirection->next->assembled,
			NULL, "No such file or directory", NULL);
	return (false);
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
		fd_redir = get_fd(shell, redirection);
		if (fd_redir == -1)
			return (file_access_fail(shell, redirection));
		if (dup_fd(fd_redir, redirection) == false)
			return (false);
		close(fd_redir);
		redirection = redirection->next->next;
	}
	side_fd_manager(shell, pipetab, side);
	close_pipe(tree->garbage_pipe);
	previous_pipe_manager(tree, side);
	return (true);
}
