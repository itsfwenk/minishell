/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:19:24 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/21 17:22:36 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	t_byte	*cast_dest;
	t_byte	*cast_src;

	i = 0;
	cast_dest = (t_byte *)dest;
	cast_src = (t_byte *)src;
	while (i < n && (dest || src))
	{
		cast_dest[i] = cast_src[i];
		i++;
	}
	return (dest);
}
