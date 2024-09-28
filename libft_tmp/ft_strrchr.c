/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:28:41 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/21 14:45:28 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	cast_c;	

	i = ft_strlen(s);
	cast_c = (char)c;
	while (i > 0)
	{
		if (s[i] == cast_c)
			break ;
		i--;
	}
	if (s[i] == cast_c)
		return ((char *)s + i);
	return (NULL);
}
