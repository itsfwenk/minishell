/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:32:27 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/23 11:35:28 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	cast_start;
	size_t	slen;
	char	*result;

	i = 0;
	cast_start = (size_t)start;
	slen = ft_strlen(s);
	if (cast_start >= slen)
		len = 0;
	else if (cast_start + len >= slen)
		len = slen - cast_start;
	else if (cast_start < slen && len >= slen)
		len -= cast_start;
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (result)
	{
		while (s[i] && i < len)
		{
			result[i] = s[cast_start + i];
			i++;
		}
	}
	return (result);
}
