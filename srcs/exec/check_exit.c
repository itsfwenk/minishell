/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:15:58 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/06 17:28:14 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

void	check_cmd_path(t_skibidi *shell, t_token *tree, char *cmd_path)
{
	if (tree->argv[0][0])
		cmd_no_perm(shell, tree, cmd_path);
	else if (tree->tstring->between_quote)
		cmd_not_found(shell, tree, cmd_path);
}

bool	check_exit(t_skibidi *shell, t_token *tree, int *pipetab, t_side side)
{
	shell->to_exit = false;
	if (fd_manager(shell, tree, pipetab, side) == false)
		exit_shell(shell);
	builtin_exec(shell, tree->assembled, tree->argv, false);
	if (!ft_strcmp(tree->assembled, "exit"))
	{
		if ((shell->to_exit || !tree->argv[0]))
			exit_shell(shell);
	}
	else
		g_signal.code = 0;
	return (!shell->exit_code);
}
