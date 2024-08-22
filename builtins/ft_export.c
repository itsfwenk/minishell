/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:54:27 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/22 15:24:58 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_env **env, char **args)
{
	size_t	i;
	int		return_val;
	char	**splitted;

	i = 0;
	return_val = 0;
	while (args[i] && ft_strchr(args[i], '='))
	{
		splitted = ft_split(args[i], "=");
		if (!splitted)
			return_val = 1;
		else if (!check_key(splitted[0]))
		{
			ft_print_error("export", args[i], "not a valid identifier", "`'");
			return_val = 1;
		}
		else
			add_env(env, splitted[0], ft_strchr(args[i], '=') + 1);
		free_all(splitted);
		i++;
	}
	return (return_val);
}
