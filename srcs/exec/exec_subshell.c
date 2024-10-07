/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:26:03 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/07 13:49:59 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	subshell_pipe_manager(t_skibidi *shell, t_token *tree,
	int *pipetab, t_side side)
{
	if (pipetab && side == LEFT)
		dup2(pipetab[1], STDOUT_FILENO);
	else if (pipetab && side == RIGHT)
		dup2(pipetab[0], STDIN_FILENO);
	if (tree->previous_pipe && side == RIGHT)
		dup2(tree->previous_pipe[1], STDOUT_FILENO);
	close_pipe(tree->previous_pipe);
	close_garbage(tree->garbage_pipe);
	close(shell->stdin_save);
	close(shell->stdout_save);
	close_pipe(pipetab);
}

static void	subshell_only_redirs(t_skibidi *shell, t_token *tree)
{
	expd_wc_only_redir(shell, tree->sub_shell);
	open_only_redir(shell, tree->sub_shell);
	exit_shell(shell);
}

static bool	subshell_fd_manager(t_skibidi *shell, t_token *tree)
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
	close_garbage(tree->garbage_pipe);
	return (true);
}

static void	subshell_child_exec(t_skibidi *shell, t_token *tree,
	int *pipetab, t_side side)
{
	t_token	*par_tree;
	t_token	*sub_token;

	subshell_pipe_manager(shell, tree, pipetab, side);
	if (only_redirs(tree->sub_shell))
		return (subshell_only_redirs(shell, tree));
	par_tree = create_tree(tree->sub_shell);
	if (exec_tree(shell, par_tree, NULL, side) == true)
	{
		sub_token = tree->sub_shell;
		signal(SIGQUIT, SIG_IGN);
		while (sub_token)
		{
			if ((sub_token->type == STR || sub_token->type == PAR_STR)
				&& sub_token->pid)
			{
				if (waitpid(sub_token->pid->p_id,
						&sub_token->pid->status, 0) != -1)
					update_error_code(shell, sub_token->pid->status, false);
			}
			sub_token = sub_token->next;
		}
	}
	unlink_heredoc(shell, tree->sub_shell);
	exit_shell(shell);
}

void	exec_parentheses(t_skibidi *shell, t_token *tree, int *pipetab,
	t_side side)
{
	shell->in_par = true;
	check_for_heredoc(shell, tree);
	check_for_heredoc(shell, tree->sub_shell);
	tree->pid->p_id = fork();
	if (tree->pid->p_id == -1)
		exit_shell(shell);
	if (tree->pid->p_id == 0)
	{
		if (subshell_fd_manager(shell, tree) == false)
			exit_shell(shell);
		subshell_child_exec(shell, tree, pipetab, side);
	}
	shell->in_par = false;
}
