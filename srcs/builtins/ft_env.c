/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:14 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/05 21:29:30 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static bool	only_env(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "env"))
			return (false);
		i++;
	}
	return (true);
}

static char	*get_wrong_env(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "env"))
			return (args[i]);
		i++;
	}
	return (NULL);
}

int	ft_env(t_env *env, char **args)
{
	t_env	*path;

	path = get_env(env, "PATH");
	if ((path && path->is_unset) || !only_env(args))
	{
		if (args[0])
			ft_print_error("env", get_wrong_env(args),
				"No such file or directory", "''");
		else
			ft_print_error("env", NULL, "No such file or directory", NULL);
		return (127);
	}
	while (env)
	{
		if (env->is_unset == false && env->is_exported && check_key(env->key))
		{
			printf("%s=", env->key);
			if (env->value)
				printf("%s", env->value);
			printf("\n");
		}
		env = env->next;
	}
	return (false);
}
