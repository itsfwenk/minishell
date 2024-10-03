/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:15:58 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/03 11:37:53 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

bool	check_exit(t_skibidi *shell, t_token *tree)
{
	builtin_exec(shell, tree->assembled, tree->argv, false);
	if (!ft_strcmp(tree->assembled, "exit"))
	{
		g_signal.code = 0;
		exit_shell(shell);
	}
	return (!shell->exit_code);
}
