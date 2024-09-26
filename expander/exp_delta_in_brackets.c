/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_delta_in_brackets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:18:39 by fli               #+#    #+#             */
/*   Updated: 2024/09/26 11:47:38 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_key_in_brackets(char *str, int *limits)
{
	int	i;

	i = limits[0] + 1;
	while (i <= limits[1])
	{
		if (limits[1] == limits[0] + 2 && (str[i] == '#'
				|| str[i] == '!'
				|| str[i] == '$'
				|| str[i] == '-'))
			break ;
		if ((i == limits[0] + 1 && !ft_isalpha(str[i])
				&& str[i] != '_')
			|| (i > limits[0] + 1 && !ft_isalnum(str[i])
				&& str[i] != '_'))
		{
			ft_dprintf(2, "%sskibidishell: %s: %s%s\n", RED, str, \
			"bad substitution", END_COLOR);
			return (FALSE);
		}
		i++;
	}
	limits[0] = limits[0] + 1;
	limits[1] = limits[1] - 1;
	return (TRUE);
}

static int	exp_in_brackets(char *str,
	t_skibidi *skibidishell, int *i, int *delta_char)
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
	if (check_key_in_brackets(str, key_limits) == FALSE)
		return (FALSE);
	env_var = key_exists(str, skibidishell, key_limits);
	var_len = key_limits[1] - key_limits[0] + 3;
	*i = key_limits[1] + 2;
	if (env_var != NULL)
	{
		*delta_char = *delta_char + ft_strlen(env_var->value) - (var_len);
		return (TRUE);
	}
	*delta_char = *delta_char -(var_len);
	return (TRUE);
}

int	exp_check_keys(char *str,
	t_skibidi *skibidishell, int *i, int *delta_char)
{
	if (str[*i + 1] == '{')
	{
		if (exp_in_brackets(str, skibidishell, i, delta_char) == FALSE)
			return (FALSE);
	}
	else
		exp_no_brackets(str, skibidishell, i, delta_char);
	return (TRUE);
}
