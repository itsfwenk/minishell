/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:06:48 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 15:33:52 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

void	free_str_tab(char	**tab)
{
	size_t	i;

	i = 0;
	if (!tab || !(*tab))
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
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
	exit_code = shell->exit_code;
	free_env(shell->env);
	free(shell);
	rl_clear_history();
	exit(exit_code);
	return (exit_code);
}
