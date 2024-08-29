/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:04:48 by fli               #+#    #+#             */
/*   Updated: 2024/05/22 17:13:41 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstinit;

	i = 0;
	dstinit = ft_strlen(dst);
	if (size <= dstinit)
		return (size + ft_strlen(src));
	else
	{
		while (i < size - dstinit - 1 && src[i] != '\0')
		{
			dst[dstinit + i] = src[i];
			i++;
		}
		dst[dstinit + i] = '\0';
	}
	return (dstinit + ft_strlen(src));
}
