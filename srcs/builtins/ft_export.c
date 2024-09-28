/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:07:29 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 19:23:29 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

int	ft_export(t_skibidi *shell, char **args)
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
			ft_print_error("export", args[i], "not a valid identifier", "`'");
			return_val = 1;
		}
		else if (ft_strchr(args[i], '=') && !add_env(&shell->env,
				splitted[0], ft_strchr(args[i], '=') + 1))
			return (free_str_tab(splitted), exit_shell(shell), 2);
		free_str_tab(splitted);
		i++;
	}
	return (return_val);
}
