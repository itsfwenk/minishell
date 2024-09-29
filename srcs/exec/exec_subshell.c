/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:26:03 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/29 10:32:50 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	subshell_child_exec(t_skibidi *shell, t_token *tree,
	int *pipetab, t_side side)
{
	t_token	*par_tree;
	t_token	*sub_token;

	dup2(pipetab[0], STDIN_FILENO);
	close_pipe(pipetab);
	par_tree = create_tree(tree->sub_shell);
	if (exec_tree(shell, par_tree, NULL, side) == true)
	{
		sub_token = tree->sub_shell;
		while (sub_token)
		{
			if (sub_token->type == STR)
				waitpid(sub_token->pid->p_id,
					&sub_token->pid->status, 0);
			sub_token = sub_token->next;
		}
		exit(EXIT_SUCCESS);
	}
}

void	exec_parentheses(t_skibidi *shell, t_token *tree, int *pipetab,
	t_side side)
{
	tree->pid = ft_lstnew_pipex(shell);
	if (tree->pid == NULL)
		exit_shell(shell);
	tree->pid->p_id = fork();
	if (tree->pid->p_id == -1)
		exit_shell(shell);
	if (tree->pid->p_id == 0)
		subshell_child_exec(shell, tree, pipetab, side);
	close_pipe(pipetab);
	waitpid(tree->pid->p_id, &tree->pid->status, 0);
}
