/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:55:15 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/21 14:01:17 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < siz && dst[i])
		i++;
	if (siz)
	{
		while (i + j < siz - 1 && src[j])
		{
			dst[i + j] = src[j];
			j++;
		}
	}
	if (i < siz)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
