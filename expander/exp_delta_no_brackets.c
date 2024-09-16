/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_delta_no_brackets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:22:26 by fli               #+#    #+#             */
/*   Updated: 2024/09/16 18:00:44 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_var_limiter(t_string *current, int *key_limits)
{
	if ((current->str[key_limits[0]] == '#'
			|| current->str[key_limits[0]] == '!'
			|| current->str[key_limits[0]] == '$'
			|| current->str[key_limits[0]] == '-'))
	{
		key_limits[1] = key_limits[1] + 1;
		return (TRUE);
	}
	if ((key_limits[1] == key_limits[0]
			&& !ft_isalpha(current->str[key_limits[1]])
			&& current->str[key_limits[1]] != '_')
		|| (key_limits[1] > key_limits[0]
			&& !ft_isalnum(current->str[key_limits[1]])
			&& current->str[key_limits[1]] != '_'))
		return (TRUE);
	return (FALSE);
}

t_env	*key_exists(t_string *current, t_skibidi *skibidishell, int *limits)
{
	int		tstring_i;
	int		key_i;
	t_env	*env_var;

	env_var = skibidishell->env;
	while (env_var != NULL)
	{
		tstring_i = limits[0];
		key_i = 0;
		if (current->str[tstring_i] == env_var->key[key_i]
			&& env_var->is_unset == FALSE)
		{
			while (tstring_i <= limits[1] && env_var->key[key_i] != '\0')
			{
				tstring_i++;
				key_i++;
				if (current->str[tstring_i] != env_var->key[key_i])
					break ;
			}
			if (tstring_i == limits[1] + 1 && env_var->key[key_i] == '\0')
				return (env_var);
		}
		env_var = env_var->next;
	}
	return (NULL);
}

void	exp_no_brackets(t_string *current,
	t_skibidi *skibidishell, int *i, int *delta_char)
{
	int		key_limits[2];
	int		key_len;
	t_env	*env_var;

	key_limits[0] = *i + 1;
	key_limits[1] = key_limits[0];
	while (current->str[key_limits[1]] != '\0')
	{
		if (is_var_limiter(current, key_limits) == TRUE)
			break ;
		key_limits[1]++;
	}
	key_limits[1]--;
	env_var = key_exists(current, skibidishell, key_limits);
	key_len = key_limits[1] - key_limits[0] + 2;
	*i = key_limits[1] + 1;
	if (env_var != NULL)
	{
		*delta_char = *delta_char + ft_strlen(env_var->value) - (key_len);
		return ;
	}
	*delta_char = *delta_char -(key_len);
	return ;
}
