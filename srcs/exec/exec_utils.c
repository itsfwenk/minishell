/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:26:23 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 17:44:21 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static char	*env_to_line(t_env *env)
{
	size_t	key_len;
	size_t	full_len;
	size_t	i;
	char	*line;

	key_len = ft_strlen(env->key);
	full_len = key_len + ft_strlen(env->value) + 1;
	line = ft_calloc(full_len + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < key_len)
	{
		line[i] = env->key[i];
		i++;
	}
	line[i] = '=';
	i++;
	while (i < full_len)
	{
		line[i] = env->value[i - key_len - 1];
		i++;
	}
	return (line);
}

static size_t	env_size(t_env *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		if (check_key(env->key) && !env->is_unset)
			size++;
		env = env->next;
	}
	return (size);
}

char	**build_envp(t_env *env)
{
	size_t	size;
	size_t	i;
	char	**envp;

	size = env_size(env);
	if (!size)
		return (NULL);
	envp = ft_calloc(size + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (check_key(env->key) && !env->is_unset)
		{
			envp[i] = env_to_line(env);
			if (!envp[i])
				return (free_str_tab(envp));
			i++;
		}
		env = env->next;
	}
	return (envp);
}