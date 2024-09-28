/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:50:32 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/23 23:46:36 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	t_byte			*cast_s;
	unsigned char	cast_c;

	i = 0;
	cast_c = (unsigned char)c;
	cast_s = (t_byte *)s;
	while (i < n)
	{
		if (cast_s[i] == cast_c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
