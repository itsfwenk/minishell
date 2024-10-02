/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:55:26 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/02 18:00:12 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	add_tpipe(t_skibidi *shell, t_pipe **garbage, int *to_add)
{
	t_pipe	*tpipe_to_add;
	t_pipe	*last_garbage_pipe;

	if (to_add == NULL)
		return ;
	last_garbage_pipe = *garbage;
	while (last_garbage_pipe && last_garbage_pipe->next)
	{
		last_garbage_pipe = last_garbage_pipe->next;
	}
	tpipe_to_add = ft_calloc(1, sizeof(t_pipe));
	if (tpipe_to_add == NULL)
		exit_shell(shell);
	tpipe_to_add->pipefd = to_add;
	if (last_garbage_pipe == NULL)
		*garbage = tpipe_to_add;
	else
		last_garbage_pipe->next = tpipe_to_add;
}

static void	add_garbage(t_skibidi *shell, t_token *tree,
	t_pipe **garbage, int *pipetab)
{
	t_pipe	*current;

	current = tree->garbage_pipe;
	while (current)
	{
		add_tpipe(shell, garbage, current->pipefd);
		current = current->next;
	}
	add_tpipe(shell, garbage, pipetab);
}

void	close_garbage(t_pipe *garbage)
{
	t_pipe	*current;

	current = garbage;
	while (current)
	{
		close_pipe(current->pipefd);
		current = current->next;
	}
}

void	free_tpipe(t_pipe *to_free)
{
	t_pipe	*tmp;

	while (to_free)
	{
		tmp = to_free->next;
		free(to_free);
		to_free = tmp;
	}
}

void	pipe_manager(t_skibidi *shell, t_token *tree, int *pipetab, t_side side)
{
	if (pipetab && side == LEFT)
	{
		tree->right->previous_pipe = pipetab;
		add_garbage(shell, tree, &tree->left->garbage_pipe, pipetab);
		add_garbage(shell, tree, &tree->right->garbage_pipe, NULL);
	}
	else if (pipetab && side == RIGHT)
	{
		tree->left->previous_pipe = pipetab;
		add_garbage(shell, tree, &tree->right->garbage_pipe, pipetab);
	}
	if (pipe(tree->pid->pipefd) == -1)
		exit_shell(shell);
}
