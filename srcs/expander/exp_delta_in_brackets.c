/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_delta_in_brackets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:50:15 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/06 02:13:15 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static bool	check_key_in_brackets(char *str, int *limits)
{
	int	i;

	i = limits[0] + 1;
	while (i < limits[1])
	{
		if (limits[1] == limits[0] + 2 && in_charset(str[i], "#!$-?"))
			break ;
		if (is_space(str[i])
			|| (i == limits[0] + 1 && !ft_isalpha(str[i])
				&& str[i] != '_')
			|| (i > limits[0] + 1 && !ft_isalnum(str[i])
				&& str[i] != '_'))
		{
			ft_print_error(NULL, str, "bad substitution", "\0");
			free(str);
			return (false);
		}
		i++;
	}
	limits[0] = limits[0] + 1;
	limits[1] = limits[1] - 1;
	return (true);
}

static bool	exp_in_brackets(t_skibidi *shell, char *str,
	int *i, int *delta_char)
{
	int		key_limits[2];
	int		var_len;
	t_env	*env_var;

	key_limits[0] = *i + 1;
	key_limits[1] = key_limits[0];
	while (str[key_limits[1]] != '\0')
	{
		if (str[key_limits[1]] == '}')
			break ;
		key_limits[1]++;
	}
	if (check_key_in_brackets(str, key_limits) == false)
		return (false);
	env_var = key_exists(shell, str, key_limits);
	var_len = key_limits[1] - key_limits[0] + 3;
	*i = key_limits[1] + 2;
	if (env_var != NULL)
	{
		*delta_char = *delta_char + ft_strlen(env_var->value) - (var_len);
		return (true);
	}
	*delta_char = *delta_char -(var_len);
	return (true);
}

bool	exp_check_keys(t_skibidi *shell, char *str,
	int *i, int *delta_char)
{
	if (str[*i + 1] == '{')
	{
		if (exp_in_brackets(shell, str, i, delta_char) == false)
			return (false);
	}
	else
		exp_no_brackets(shell, str, i, delta_char);
	return (true);
}
