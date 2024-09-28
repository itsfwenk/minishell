/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:10:19 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/22 11:15:02 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = ft_strlen(s);
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (result)
	{
		i = 0;
		while (i < len)
		{
			result[i] = s[i];
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}
