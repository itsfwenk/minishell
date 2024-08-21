/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:35:13 by fli               #+#    #+#             */
/*   Updated: 2024/05/22 12:13:03 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*strmapi;

	strmapi = ft_strdup(s);
	if (strmapi == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		strmapi[i] = f(i, strmapi[i]);
		i++;
	}
	return (strmapi);
}
