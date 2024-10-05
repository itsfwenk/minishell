/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:15:58 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/05 10:32:40 by fli              ###   ########.fr       */
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
	if (!ft_strcmp(tree->assembled, "exit")
		&& (shell->to_exit || !tree->argv[0]))
		exit_shell(shell);
	return (!shell->exit_code);
}
