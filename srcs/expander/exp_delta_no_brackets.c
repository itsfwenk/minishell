/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_delta_no_brackets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:55:40 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 18:04:12 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static bool	is_var_limiter(char *str, int *key_limits)
{
	if ((str[key_limits[0]] == '#'
			|| str[key_limits[0]] == '!'
			|| str[key_limits[0]] == '$'
			|| str[key_limits[0]] == '-'))
	{
		key_limits[1] = key_limits[1] + 1;
		return (true);
	}
	if ((key_limits[1] == key_limits[0]
			&& !ft_isalpha(str[key_limits[1]])
			&& str[key_limits[1]] != '_')
		|| (key_limits[1] > key_limits[0]
			&& !ft_isalnum(str[key_limits[1]])
			&& str[key_limits[1]] != '_'))
		return (true);
	return (false);
}

t_env	*key_exists(t_skibidi *shell, char *str, int *limits)
{
	int		tstring_i;
	int		key_i;
	t_env	*env_var;

	env_var = shell->env;
	while (env_var != NULL)
	{
		tstring_i = limits[0];
		key_i = 0;
		if (str[tstring_i] == env_var->key[key_i]
			&& env_var->is_unset == false)
		{
			while (tstring_i <= limits[1] && env_var->key[key_i] != '\0')
			{
				tstring_i++;
				key_i++;
				if (str[tstring_i] != env_var->key[key_i])
					break ;
			}
			if (tstring_i == limits[1] + 1 && env_var->key[key_i] == '\0')
				return (env_var);
		}
		env_var = env_var->next;
	}
	return (NULL);
}

void	exp_no_brackets(t_skibidi *shell, char *str,
	int *i, int *delta_char)
{
	int		key_limits[2];
	int		key_len;
	t_env	*env_var;

	key_limits[0] = *i + 1;
	key_limits[1] = key_limits[0];
	while (str[key_limits[1]] != '\0')
	{
		if (is_var_limiter(str, key_limits) == true)
			break ;
		key_limits[1]++;
	}
	key_limits[1]--;
	env_var = key_exists(shell, str, key_limits);
	key_len = key_limits[1] - key_limits[0] + 2;
	*i = key_limits[1] + 1;
	if (env_var != NULL)
	{
		*delta_char = *delta_char + ft_strlen(env_var->value) - (key_len);
		return ;
	}
	*delta_char = *delta_char - (key_len);
	return ;
}