/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:17:37 by fli               #+#    #+#             */
/*   Updated: 2024/05/23 11:29:10 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return (&((char *)big)[0]);
	while (i < len && j < len && (big[i] != '\0'))
	{
		while (i + j < len && big[i + j] == little[j])
		{
			if (little[j + 1] == '\0')
				return (&((char *)big)[i]);
			else
				j++;
		}
		if (j + 1 <= len)
		{
			i++;
			j = 0;
		}
	}
	return (NULL);
}
