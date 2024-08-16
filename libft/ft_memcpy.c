/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:44:54 by fli               #+#    #+#             */
/*   Updated: 2024/05/22 17:31:34 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (&((char *)dst)[0]);
}

/* #include <stdio.h>
int     main()
{
        char str[4] = "oui";
	char str2[4] = "non";
        printf("%s\n", (char *)ft_memcpy((char*)&str[0], (char*)&str2[0], 3));
} */
