/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:52:29 by fli               #+#    #+#             */
/*   Updated: 2024/05/22 17:26:07 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if ((char)c == '\0')
		return (&((char *)s)[ft_strlen(s)]);
	i = ft_strlen(s);
	while (i >= 0)
	{
		if ((char)s[i] == (char)c)
			return (&((char *)s)[i]);
		i--;
	}
	return (NULL);
}
