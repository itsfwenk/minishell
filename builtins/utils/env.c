/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:30:17 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/19 15:45:37 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

static t_env	*env_get_last(t_env *env)
{
	while (env)
	{
		if (!env->next)
			return (env);
		env = env->next;
	}
	return (env);
}

static void	env_add_back(t_env **env, t_env *val)
{
	t_env	*last;

	last = env_get_last(*env);
	if (last)
		last->next = val;
	else
		*env = val;
}

t_env	*get_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key) && !env->deleted)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*add_env(t_env **env, char *key, char *value)
{
	t_env	*cur_env;
	t_env	*new_val;

	cur_env = *env;
	new_val = get_env(*env, key);
	if (new_val)
	{
		if (new_val->value)
			free(new_val->value);
		new_val->value = ft_strdup(value);
	}
	else
	{
		new_val = (t_env *)malloc(sizeof(t_env));
		if (new_val)
		{
			new_val->key = ft_strdup(key);
			new_val->value = ft_strdup(value);
			new_val->next = NULL;
			env_add_back(env, new_val);
		}
	}
	if (new_val)
		new_val->deleted = 0;
	return (new_val);
}

void	del_env(t_env **env, char *key)
{
	t_env	*val;

	val = get_env(*env, key);
	if (val)
		val->deleted = 1;
}
