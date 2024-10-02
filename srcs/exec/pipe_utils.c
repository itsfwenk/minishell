/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:55:26 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/02 11:58:38 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

void	pipe_manager(t_skibidi *shell, t_token *tree, int *pipetab, t_side side)
{
	if (pipetab && side == LEFT)
	{
		tree->right->previous_pipe = pipetab;
		tree->left->garbage_pipe = pipetab;
	}
	else if (pipetab && side == RIGHT)
	{
		tree->left->previous_pipe = pipetab;
		tree->right->garbage_pipe = pipetab;
	}
	if (pipe(tree->pid->pipefd) == -1)
		exit_shell(shell);
	pipetab = tree->pid->pipefd;
}
