/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:20:53 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/21 14:25:15 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	cast_c;

	i = 0;
	cast_c = (char)c;
	while (s[i])
	{
		if (s[i] == cast_c)
			break ;
		i++;
	}
	if (s[i] == cast_c)
		return ((char *)s + i);
	return (NULL);
}
