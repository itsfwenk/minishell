/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:08:19 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 19:08:26 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

int	ft_unset(t_env *env, char **keys)
{
	size_t	i;

	i = 0;
	while (keys[i])
	{
		if (check_key(keys[i]))
			unset_env(env, keys[i]);
		i++;
	}
	return (0);
}
