/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:41:07 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/17 19:55:56 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec_tree(t_token *tree)
// {
// 	if (!tree)
// 		return ;
// 	exec_tree(tree->left);
// 	ft_dprintf(2, "%s %s %s\n", tree->left->full_string, tree->full_string, tree->right->full_string);
// 	exec_tree(tree->right);
// }

// int	ft_exec(t_skibidi *skibidishell)
// {
// 	t_token	*tree;

// 	tree = skibidishell->tree;
// }

void	exec_parentheses(t_skibidi *skibidishell, t_token *tree)
{
	if (tree->type == PAR_STR)
	{
		tree->pid = ft_lstnew_pipex(tree);
		if (tree->pid == NULL || pipe(tree->pid->pipefd) == -1)
			ft_free_clean(skibidishell);
		tree->pid->p_id = fork();
		if (tree->pid->p_id == -1)
			ft_free_clean(skibidishell);
		if (tree->pid->p_id == 0)
			exec_tree(skibidishell, create_tree(tree->sub_shell), -1, -1);
	}
}

int	fd_manager(t_token *tree, int *pipetab, int side)
{
	int	fd_in;


}

void	exec_cmd(t_skibidi *skibidishell, t_token *tree, int *pipetab, int side)
{
	if (tree->type == STR)
	{
		tree->pid = ft_lstnew_pipex(tree, skibidishell);
		tree->pid->p_id = fork();
		if (tree->pid->p_id == -1)
			ft_free_clean(skibidishell);
		if (tree->pid->p_id == 0)
		{

		}
	}
}

int	exec_tree(t_skibidi *skibidishell, t_token *tree, int *pipetab, int side)
{
	int	exit_code;

	if (tree == NULL)
		return ;
	if (tree->type == PIPE)
	{
		if (pipe(tree->pid->pipefd) == -1)
			ft_free_clean(skibidishell);
		pipetab = tree->pid->pipefd;
	}
	exit_code = exec_tree(skibidishell, tree->left, pipetab, LEFT);
	if ((tree->type == AND && exit_code == TRUE) || tree->type == PIPE)
		exit_code = exec_tree(skibidishell, tree->right, pipetab, RIGHT);
	exec_parentheses(skibidishell, tree);
	exec_cmd(skibidishell, tree, pipetab, side);
}
