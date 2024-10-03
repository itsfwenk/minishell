/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:14 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 00:47:50 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

int	ft_env(t_env *env, char **args)
{
	t_env	*path;

	path = get_env(env, "PATH");
	if (!path || path->is_unset || args[0])
	{
		if (args[0])
			ft_print_error("env", args[0], "No such file or directory", "''");
		else
			ft_print_error("env", NULL, "No such file or directory", NULL);
		return (127);
	}
	while (env)
	{
		if (env->is_unset == false && check_key(env->key))
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
