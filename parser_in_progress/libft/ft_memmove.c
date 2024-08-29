/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:45:53 by fli               #+#    #+#             */
/*   Updated: 2024/05/22 17:33:20 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (dst < src)
	{
		i = 0;
		while (i < len)
		{	
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			i--;
			((char *)dst)[i] = ((char *)src)[i];
		}
	}
	return (&((char *)dst)[0]);
}

/* #include <stdio.h>
int	main()
{
	char str[4] = "oui";
	printf("%s\n", (char *)ft_memmove((char*)&str[1], (char*)&str[0], 2));
} */
