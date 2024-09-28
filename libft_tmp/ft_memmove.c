/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:19:30 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/22 17:21:26 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	t_byte	*cast_dest;
	t_byte	*cast_src;

	i = 0;
	cast_dest = (t_byte *)dest;
	cast_src = (t_byte *)src;
	if (dest || src)
	{
		if (dest > src)
		{
			while (n--)
				cast_dest[n] = cast_src[n];
		}
		else
		{
			while (i < n)
			{
				cast_dest[i] = cast_src[i];
				i++;
			}
		}
	}
	return (dest);
}
