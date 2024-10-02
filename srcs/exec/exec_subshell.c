/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:26:03 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/02 18:30:47 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	subshell_pipe_manager(t_token *tree, int *pipetab, t_side side)
{
	if (pipetab && side == LEFT)
		dup2(pipetab[1], STDOUT_FILENO);
	else if (pipetab && side == RIGHT)
		dup2(pipetab[0], STDIN_FILENO);
	if (tree->previous_pipe && side == RIGHT)
		dup2(tree->previous_pipe[1], STDOUT_FILENO);
	close_pipe(tree->previous_pipe);
	close_garbage(tree->garbage_pipe);
	close_pipe(pipetab);
}

static void	subshell_only_redirs(t_skibidi *shell, t_token *tree)
{	
	expd_wc_only_redir(shell, tree->sub_shell);
	check_for_here_doc(shell, tree->sub_shell);
	open_only_redir(shell, tree->sub_shell);
	lx_deltokens(&shell->tokens);
	free_env(shell->env);
	free(shell);
	exit(EXIT_SUCCESS);
}

static void	subshell_child_exec(t_skibidi *shell, t_token *tree,
	int *pipetab, t_side side)
{
	t_token	*par_tree;
	t_token	*sub_token;

	subshell_pipe_manager(tree, pipetab, side);
	if (only_redirs(tree->sub_shell))
		return (subshell_only_redirs(shell, tree));
	par_tree = create_tree(tree->sub_shell);
	if (exec_tree(shell, par_tree, NULL, side) == true)
	{
		sub_token = tree->sub_shell;
		while (sub_token)
		{
			if (sub_token->type == STR)
				waitpid(sub_token->pid->p_id, &sub_token->pid->status, 0);
			sub_token = sub_token->next;
		}
		lx_deltokens(&shell->tokens);
		free_env(shell->env);
		free(shell);
		exit(EXIT_SUCCESS);
	}
}

void	exec_parentheses(t_skibidi *shell, t_token *tree, int *pipetab,
	t_side side)
{
	tree->pid->p_id = fork();
	if (tree->pid->p_id == -1)
		exit_shell(shell);
	if (tree->pid->p_id == 0)
		subshell_child_exec(shell, tree, pipetab, side);
	if (pipetab && side == RIGHT)
		close_pipe(pipetab);
	if (waitpid(tree->pid->p_id, &tree->pid->status, 0) != -1)
		update_error_code(shell, tree->pid->status);
}
