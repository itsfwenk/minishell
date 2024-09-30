/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:29:52 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/30 11:51:01 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

t_skibidi	*init_shell(char **envp)
{
	t_skibidi	*shell;

	shell = ft_calloc(1, sizeof(t_skibidi));
	if (!shell || ft_export(shell, envp))
		return (NULL);
	if (add_env(&shell->env, "#", "0") == NULL)
		exit_shell(shell);
	if (add_env(&shell->env, "?", "0") == NULL)
		exit_shell(shell);
	if (add_env(&shell->env, "!", "last background job pid") == NULL)
		exit_shell(shell);
	if (add_env(&shell->env, "$", "shell pid") == NULL)
		exit_shell(shell);
	if (add_env(&shell->env, "_", "minishell") == NULL)
		exit_shell(shell);
	if (add_env(&shell->env, "-", "himBHs") == NULL)
		exit_shell(shell);
	return (shell);
}
