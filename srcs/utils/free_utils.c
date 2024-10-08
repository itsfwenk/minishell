/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:06:48 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/05 10:25:44 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

char	**free_str_tab(char	**tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	free_env(t_env	*env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

int	exit_shell(t_skibidi *shell)
{
	int	exit_code;

	if (!shell)
		return (EXIT_FAILURE);
	close(shell->stdin_save);
	close(shell->stdout_save);
	exit_code = shell->exit_code;
	lx_deltokens(&shell->tokens);
	free_env(shell->env);
	free(shell);
	rl_clear_history();
	if (exit_code)
	{
		exit(exit_code);
		return (exit_code);
	}
	exit(g_signal.code);
	return (g_signal.code);
}
