/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:15:58 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 00:26:53 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

bool	check_exit(t_skibidi *shell, t_token *tree)
{
	shell->to_exit = false;
	builtin_exec(shell, tree->assembled, tree->argv, false);
	if (!ft_strcmp(tree->assembled, "exit")
		&& (shell->to_exit || !tree->argv[0]))
		exit_shell(shell);
	return (!shell->exit_code);
}
