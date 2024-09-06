/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:31:32 by fli               #+#    #+#             */
/*   Updated: 2024/09/06 14:27:14 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*get_wanted_key(t_string *current, int i)
// {
// 	int		key_limits[2];
// 	char	*wanted_key;

// 	key_limits[0] = i + 1;
// 	key_limits[1] = key_limits[0] + 1;
// 	while (current->str[key_limits[1]] != NULL)
// 	{
// 		if (ft_isalnum(current->str[key_limits[1]]) == FALSE
// 			&& current->str[key_limits[1]] != '_')
// 			break;
// 		key_limits[1]++;
// 	}
// 	key_limits[1]--;
// 	wanted_key = lx_strdup(current->str, key_limits);
// 	if (wanted_key == NULL)
// 		return (NULL); // ft_exit
// 	return (wanted_key);
// }

void	exp_find_key_limits(t_string *current, int i, int *key_limits)
{
	key_limits[0] = i + 1;
	if (current->str[i + 1] == '{')
		key_limits[0] = i + 2;
	key_limits[1] = key_limits[0];

	while (current->str[key_limits[1]] != '\0')
	{
		if (current->str[i + 1] == '{'
			&& current->str[key_limits[1]] == '}')
			break;
		if (current->str[i + 1] != '{'
			&& (key_limits[1] == key_limits[0]
					&& !ft_isalpha(current->str[key_limits[1]])
					&& current->str[key_limits[1]] != '_')
				|| (key_limits[1] > key_limits[0]
					&& !ft_isalnum(current->str[key_limits[1]])
					&& current->str[key_limits[1]] != '_'))
			break;
		key_limits[1]++;
	}
	key_limits[1]--;
}

static void	exp_cp_env_var(t_string *current,
	t_skibidi *skibidishell, char *expanded_str, int *i)
{
	int		j;
	int		key_limits[2];
	t_env	*env_var;

	exp_find_key_limits(current, i[0], key_limits);
	env_var = key_exist(current, skibidishell, key_limits);
	j = 0;
	while (env_var != NULL && env_var->is_unset == FALSE
		&& env_var->value[j] != '\0')
	{
		expanded_str[i[1]] = env_var->value[j];
		i[1]++;
		j++;
	}
	if (current->str[i[0] + 1] == '{')
		i[0] == key_limits[1] + 2;
	else
		i[0] == key_limits[1] + 1;
}

static void	exp_dup_env_var(t_string *current,
	t_skibidi *skibidishell, char *expanded_str)
{
	int		i[2];
	int		key_len;
	int		key_limits[2];
	t_env	*env_var;

	i[0] = 0;
	i[1] = 0;
	while (current->str[i[0]] != '\0')
	{
		if (current->str[i[0]] == '$' && current->str[i[0] + 1] != '\0')
		{
			exp_cp_env_vat(current, skibidishell, expanded_str, i);
			continue;
		}
		expanded_str[i[1]] = current->str[i[0]];
		i[0]++;
		i[1]++;
	}
	expanded_str[i[1]] = '\0';
	free(current->str);
	current->str = expanded_str;
}

int	exp_env_var(t_string *current, t_skibidi *skibidishell)
{
	int		i;
	int		delta_char;
	int		nb_exp_var;
	char	*expanded_str;

	i = 0;
	delta_char = 0;
	nb_exp_var = 0;
	while (current->str[i] != '\0')
	{
		if (current->str[i] == '$' && current->str[i + 1] != '\0')
		{
			nb_exp_var++;
			if (exp_check_keys(current, skibidishell, &i, &delta_char) == FALSE)
				return (FALSE);
		}
		i++;
	}
	if (nb_exp_var == 0)
		return (TRUE);
	expanded_str = malloc(1 + (ft_strlen(current->str) + delta_char));
	if (expanded_str == NULL)
		return ; // ft_exit
	exp_dup_env_var(current, skibidishell, expanded_str);
	return (TRUE);
}
