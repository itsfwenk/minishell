/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:23:56 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/20 15:47:48 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->is_unset == FALSE)
		{
			printf("%s=", env->key);
			if (env->value)
				printf("%s", env->value);
			printf("\n");
		}
		env = env->next;
	}
	return (FALSE);
}
