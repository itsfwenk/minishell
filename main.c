/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:16:56 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/19 15:37:43 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "builtins/builtins.h"
#include <stdio.h>

static void	free_env(t_env *env)
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

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_env	*tmp;
	size_t	i;
	char	**splitted;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		splitted = ft_split(envp[i], '=');
		if (!splitted)
			return (free_env(env), 1);
		add_env(&env, splitted[0], splitted[1]);
		free_all(splitted);
		i++;
	}
	add_env(&env, "OMG", "Wouhou");
	ft_env(env);
	del_env(&env, "OMG");
	ft_env(env);
	free_env(env);
	return (0);
}
