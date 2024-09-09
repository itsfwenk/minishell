/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:54:23 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/04 14:58:21 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
