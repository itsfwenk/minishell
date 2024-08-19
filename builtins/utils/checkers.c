/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:45:49 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/19 15:46:02 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	check_key(char *key)
{
	size_t	i;

	i = 0;
	while (key[i])
	{
		if (!i && !ft_isalpha(key[i]) && key[i] != '_')
			return (0);
		if (i && !ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
