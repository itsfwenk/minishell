/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:30:17 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/19 12:55:40 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	apply_indexes(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		env->index = i;
		i++;
		env = env->next;
	}
}

int	check_key(char *key)
{
	size_t	i;

	i = 0;
	while (key[i])
	{
		if (!i && !ft_isalpha(key[i]) && key[i] != '_')
			return (0);
		if (i && !ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*get_env(char *key, t_env *env)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	while (env)
	{
		if (!ft_strncmp(env->key, key, key_len))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*add_env(char *key, char *value, t_env *env)
{
	t_env	*cur_env;
	t_env	*new_val;

	cur_env = env;
	new_val = get_env(key, env);
	if (new_val)
		new_val->value = value;
	else
	{
		new_val = (t_env *)malloc(sizeof(t_env));
		if (new_val)
		{
			new_val->key = key;
			new_val->value = value;
			apply_indexes(env);
		}
	}
	return (new_val);
}

