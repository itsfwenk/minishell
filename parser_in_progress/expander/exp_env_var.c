/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:31:32 by fli               #+#    #+#             */
/*   Updated: 2024/09/04 19:27:01 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*key_exist(t_string *current, t_skibidi *skibidishell, int *limits)
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
					break;
			}
			if (tstring_i == limits[1] + 1 && env_var->key[key_i] == '\0')
				return (env_var);
		}
		env_var = env_var->next;
	}
	return (NULL);
}

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

void	exp_no_brackets(t_string *current,
	t_skibidi *skibidishell, int *i, int *delta_char)
{
	int		key_limits[2];
	int		var_len;
	t_env	*env_var;

	key_limits[0] = *i + 1;
	key_limits[1] = key_limits[0] + 1;
	while (current->str[key_limits[1]] != '\0')
	{
		if (ft_isalnum(current->str[key_limits[1]]) == FALSE
			&& current->str[key_limits[1]] != '_')
			break;
		key_limits[1]++;
	}
	key_limits[1]--;
	env_var = key_exist(current, skibidishell, key_limits);
	var_len = key_limits[1] - key_limits[0] + 2;
	*i = key_limits[1] + 1;
	if (env_var != NULL)
	{
		*delta_char = *delta_char + ft_strlen(env_var->value) - (var_len);
		return ;
	}
	*delta_char = *delta_char -(var_len);
	return ;
}

int	check_key_in_brackets(t_string *current, int *limits)
{
	int	i;

	i = limits[0];
	while (i <= limits[1])
	{
		if ((i == limits[0] && !ft_isalpha(current->str[i])
			&& current->str[i] != '_')
			|| (i > limits[0] && !ft_isalnum(current->str[i])
				&& current->str[i] != '_'))
		{
			ft_dprintf(2, "%sskibidishell: %s: %s%s\n", RED, current->str, \
			"bad substitution", END_COLOR);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	exp_in_brackets(t_string *current,
	t_skibidi *skibidishell, int *i, int *delta_char)
{
	int		key_limits[2];
	int		var_len;
	t_env	*env_var;

	key_limits[0] = *i + 2;
	key_limits[1] = key_limits[0] + 1;
	while (current->str[key_limits[1]] != '\0')
	{
		if (current->str[key_limits[1]] == '}')
			break;
		key_limits[1]++;
	}
	key_limits[1]--;
	if (check_key_in_brackets(current, key_limits) == FALSE)
		return (FALSE);
	env_var = key_exist(current, skibidishell, key_limits);
	var_len = key_limits[1] - key_limits[0] + 2;
	*i = key_limits[1] + 1;
	if (env_var != NULL)
	{
		*delta_char = *delta_char + ft_strlen(env_var->value) - (var_len);
		return (TRUE);
	}
	*delta_char = *delta_char -(var_len);
	return (TRUE);
}

int	exp_check_keys(t_string *current,
	t_skibidi *skibidishell, int *i, int *delta_char)
{
	if (current->str[*i + 1] == '{')
	{
		if (exp_in_brackets(current, skibidishell, i, delta_char) == FALSE)
			return (FALSE);
	}
	else
		exp_no_brackets(current, skibidishell, i, delta_char);


	// while (current->str[key_limits[1]] != NULL)
	// {
	// 	if (ft_isalnum(current->str[key_limits[1]]) == FALSE
	// 		&& current->str[key_limits[1]] != '_'
	// 		|| (in_brackets == TRUE && current->str[key_limits[1]] == '}'))
	// 		break;
	// 	key_limits[1]++;
	// }
	// key_limits[1]--;
	// env_var = key_exist(current, skibidishell, key_limits);
	// var_env_len = key_limits[1] - key_limits[0] + 2;
	// *i = key_limits[1] + 1;
	// if (env_var != NULL)
	// 	return (ft_strlen(env_var->value) - (var_env_len));
	// return (-(var_env_len));
}

static void	exp_dup_env_var(t_string *current, char *expanded_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (current->str[i] != '\0')
	{
		if (current->str[i] == '$' && ft_isdigit(current->str[i + 1]) != FALSE)
		{
		// 	i = i + 2;
		// 	continue;
		// }
		// expanded_str[j] = current->str[i];
		// j++;
		// i++;
	}
	expanded_str[j] = '\0';
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
	{
		return ; // ft_exit
	}
	exp_dup_env_var(current, expanded_str);
}
