/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:08:19 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/03 23:59:15 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

int	ft_unset(t_env *env, char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (check_key(args[i]))
			unset_env(env, args[i]);
		i++;
	}
	return (0);
}
