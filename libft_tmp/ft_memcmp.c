/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:26:01 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/22 14:42:46 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	t_byte	*cast_s1;
	t_byte	*cast_s2;

	i = 0;
	cast_s1 = (t_byte *)s1;
	cast_s2 = (t_byte *)s2;
	while (i < n)
	{
		if (cast_s1[i] != cast_s2[i])
			return ((int)(cast_s1[i] - cast_s2[i]));
		i++;
	}
	return (0);
}
