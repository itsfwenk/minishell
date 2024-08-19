/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:23:56 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/19 15:37:53 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (!env->deleted)
		{
			ft_dprintf(1, "%s=", env->key);
			if (env->value)
				ft_dprintf(1, "%s", env->value);
			ft_dprintf(1, "\n");
		}
		env = env->next;
	}
	return (0);
}
