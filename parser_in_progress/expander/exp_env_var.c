/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:31:32 by fli               #+#    #+#             */
/*   Updated: 2024/09/03 17:38:12 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_env	*key_exist(t_string *current, t_skibidi *skibidishell, int *limits)
// {
// 	int	tstring_i;
// 	int	key_i;
// 	t_env	*env_var;

// 	env_var = skibidishell->env;
// 	while (env_var != NULL)
// 	{
// 		tstring_i = limits[0];
// 		key_i = 0;
// 		if (current->str[tstring_i] == env_var->key[key_i]
// 			&& env_var->is_unset == FALSE)
// 		{
// 			while (tstring_i <= limits[1] && env_var->key[key_i] != '\0')
// 			{
// 				tstring_i++;
// 				key_i++;
// 				if (current->str[tstring_i] != env_var->key[key_i])
// 					break;
// 			}
// 			if (tstring_i == limits[1] + 1 && env_var->key[key_i] == '\0')
// 				return (env_var);
// 		}
// 		env_var = env_var->next;
// 	}
// 	return (NULL);
// }

t_env	*key_exist(t_string *current, t_skibidi *skibidishell, int *limits)
{

}

char	*get_wanted_key(t_string *current, int i)
{
	int		key_limits[2];
	char	*wanted_key;

	key_limits[0] = i + 1;
	key_limits[1] = key_limits[0] + 1;
	while (current->str[key_limits[1]] != NULL)
	{
		if (current->str[key_limits[1]])
	}
}

t_env	*exp_check_keys(t_string *current, t_skibidi *skibidishell, int *i)
{
	int		key_limits[2];
	int		in_brackets;
	char	*wanted_key;

	key_limits[0] = *i + 1;
	in_brackets = FALSE;
	if (current->str[key_limits[0]] == '{')
	{
		in_brackets = TRUE;
		key_limits[0]++;
		key_limits[1] = key_limits[0] + 1;
		while ()
	}
	while (current->str[index] != '\0')
	{
		if (in_brackets == TRUE && current->str[index] == '}')
	}
}

void	exp_env_var(t_string *current, t_skibidi *skibidishell)
{
	int	i;
	int	delta_char;

	i = 0;
	delta_char = 0;
	while (current->str[i] != '\0')
	{
		if (current->str[i] == '$')
			delta_char = delta_char + exp_check_keys(current, skibidishell, &i);
	}
}
