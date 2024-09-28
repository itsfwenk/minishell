/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:57:51 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 17:01:58 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	exp_find_key_limits(char *str, int i, int *key_limits)
{
	key_limits[0] = i + 1;
	if (str[i + 1] == '{')
		key_limits[0] = i + 2;
	key_limits[1] = key_limits[0];
	while (str[key_limits[1]] != '\0')
	{
		if (str[i + 1] == '{'
			&& str[key_limits[1]] == '}')
			break ;
		if (str[i + 1] != '{'
			&& ((key_limits[1] == key_limits[0]
					&& !ft_isalpha(str[key_limits[1]])
					&& str[key_limits[1]] != '_')
				|| (key_limits[1] > key_limits[0]
					&& !ft_isalnum(str[key_limits[1]])
					&& str[key_limits[1]] != '_')))
			break ;
		key_limits[1]++;
	}
	key_limits[1]--;
}

static void	exp_cp_env_var(t_skibidi *shell, char *str,
	char *expanded_str, int *i)
{
	int		j;
	int		key_limits[2];
	t_env	*env_var;

	exp_find_key_limits(str, i[0], key_limits);
	env_var = key_exists(str, shell, key_limits);
	j = 0;
	while (env_var != NULL && env_var->is_unset == false
		&& env_var->value[j] != '\0')
	{
		expanded_str[i[1]] = env_var->value[j];
		i[1]++;
		j++;
	}
	if (str[i[0] + 1] == '{')
		i[0] = key_limits[1] + 2;
	else
		i[0] = key_limits[1] + 1;
}

static void	exp_dup_env_var(t_skibidi *shell,
	char *str, char *expanded_str)
{
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	while (str[i[0]] != '\0')
	{
		if (str[i[0]] == '$' && str[i[0] + 1] != '\0')
		{
			exp_cp_env_var(shell, str, expanded_str, i);
			continue ;
		}
		expanded_str[i[1]] = str[i[0]];
		i[0]++;
		i[1]++;
	}
	expanded_str[i[1]] = '\0';
	free(str);
	str = expanded_str;
}

int	exp_env_var(t_skibidi *shell, char *str)
{
	int		i;
	int		delta_char;
	int		nb_exp_var;
	char	*expanded_str;

	i = 0;
	delta_char = 0;
	nb_exp_var = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			nb_exp_var++;
			if (exp_check_keys(str, shell, &i, &delta_char) == false)
				return (false);
		}
		i = i + (str[i] != '\0');
	}
	if (nb_exp_var == 0)
		return (true);
	expanded_str = malloc(1 + (ft_strlen(str) + delta_char));
	if (expanded_str == NULL)
		exit_shell(shell);
	exp_dup_env_var(shell, str, expanded_str);
	return (true);
}
