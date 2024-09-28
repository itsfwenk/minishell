/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:52:49 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/23 10:57:51 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little[0])
		return ((char *)big);
	i = 0;
	j = 0;
	while (big[i] && i < len)
	{
		while (little[j] && big[i + j] == little[j])
			j++;
		if (i + j <= len && !little[j])
			return ((char *)big + i);
		j = 0;
		i++;
	}
	return (NULL);
}
