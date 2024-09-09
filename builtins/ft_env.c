/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:23:56 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/06 13:22:59 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*reset_utils_env(t_env **env)
{
	char	*itoa;
	t_env	*new_node;

	itoa = ft_itoa(g_signal);
	new_node = add_env(env, "?", itoa);
	free(itoa);
	return (new_node);
}

int	ft_env(t_env *env)
{
	if (!get_env(env, "PATH"))
	{
		ft_print_error("env", NULL, "No such file or directory", NULL);
		return (2);
	}
	while (env)
	{
		if (env->is_unset == FALSE && check_key(env->key))
		{
			printf("%s=", env->key);
			if (env->value)
				printf("%s", env->value);
			printf("\n");
		}
		env = env->next;
	}
	return (FALSE);
}
