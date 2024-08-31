/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:52:30 by fli               #+#    #+#             */
/*   Updated: 2024/05/22 15:40:34 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	cp;

	i = 0;
	if (size == 0 || !src)
		return (ft_strlen(src));
	if (ft_strlen(src) < size)
		cp = ft_strlen(src);
	else
		cp = size - 1;
	while (i < cp && src)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/* #include <stdio.h>
int	main()
{
	char dest[50];
	printf("%zu\n", ft_strlcpy(dest, "lorem ipsum dolor sit amet", 0));
}*/
