/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:07:29 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 14:31:53 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static t_env	*get_sorted_env(t_env *env, t_env *sorted)
{
	t_env	*current;
	t_env	*next;
	t_env	*tmp;

	current = env;
	while (current)
	{
		next = current->next;
		if (!sorted || ft_strcmp(current->key, sorted->key) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			tmp = sorted;
			while (tmp->next && ft_strcmp(current->key, tmp->next->key) > 0)
				tmp = tmp->next;
			current->next = tmp->next;
			tmp->next = current;
		}
		current = next;
	}
	return (sorted);
}

static void	print_export(t_env **env)
{
	t_env	*current;

	*env = get_sorted_env(*env, NULL);
	current = *env;
	while (current)
	{
		if (current->is_unset == false && check_key(current->key))
		{
			printf("export %s", current->key);
			if (current->value && current->is_exported)
				printf("=\"%s\"", current->value);
			printf("\n");
		}
		current = current->next;
	}
}

static bool	export_val(t_env **env, char *key, char *value)
{
	t_env	*new_env;
	t_env	*has_key;
	char	*end_value;

	has_key = get_env(*env, key);
	end_value = ft_strchr(value, '=');
	if (has_key && !has_key->is_unset && !end_value)
		return (true);
	if (end_value)
		new_env = add_env(env, key, end_value + 1);
	else
		new_env = add_env(env, key, "");
	if (!new_env)
		return (false);
	else if (!new_env->key || !new_env->value)
		return (false);
	new_env->is_exported = !!end_value;
	return (true);
}

int	ft_export(t_skibidi *shell, char **args, bool is_startup)
{
	size_t	i;
	int		return_val;
	char	**splitted;

	i = 0;
	return_val = 0;
	if (!args[0] && !is_startup)
		return (print_export(&shell->env), return_val);
	while (args[i])
	{
		splitted = ft_split(args[i], '=');
		if (!splitted)
			return_val = 1;
		else if (!check_key(splitted[0]))
		{
			ft_print_error("export", args[i], "not a valid identifier", "`'");
			return_val = 1;
		}
		else if (!export_val(&shell->env, splitted[0], args[i]))
			return (free_str_tab(splitted), exit_shell(shell), 2);
		free_str_tab(splitted);
		i++;
	}
	return (return_val);
}
