/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:57:46 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/22 15:02:41 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	i;
	char	*result;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	result = (char *)ft_calloc(s1len + s2len + 1, sizeof(char));
	if (result)
	{
		i = 0;
		while (i < s1len)
		{
			result[i] = s1[i];
			i++;
		}
		i = 0;
		while (i < s2len)
		{
			result[s1len + i] = s2[i];
			i++;
		}
	}
	return (result);
}
