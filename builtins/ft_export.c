/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:54:27 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/19 16:34:23 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_export(t_env **env, char **args)
{
	size_t	i;
	int		return_val;
	char	**splitted;

	i = 0;
	return_val = 0;
	while (args[i])
	{
		splitted = ft_split(args[i], '=');
		if (!splitted)
			return_val = 1;
		else if (!check_key(splitted[0]))
		{
			ft_dprintf(2, "minishell: export: `%s': \
not a valid identifier\n", args[i]);
			return_val = 1;
		}
		else
			add_env(env, splitted[0], splitted[1]);
		free_all(splitted);
		i++;
	}
	return (return_val);
}
