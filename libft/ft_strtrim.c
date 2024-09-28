/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:13:12 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/23 13:13:21 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_charset(char const c, char const *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	size_t	end;	

	len = ft_strlen(s1);
	start = 0;
	end = len - 1;
	while (s1[start] && in_charset(s1[start], set))
		start++;
	while (s1[end] && in_charset(s1[end], set))
		end--;
	if (start > end)
		return (NULL);
	return (ft_substr(s1, (unsigned int)start, (end - start + 1)));
}
