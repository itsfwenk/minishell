/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:43:01 by fli               #+#    #+#             */
/*   Updated: 2024/05/17 13:53:26 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	size_t			i;

	i = 0;
	while (i != len)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}

/* #include <stdio.h>
int	main()
{
		char str[4] = "oui";
		printf("%s\n", (char *)ft_memset((char *)&str[0], 'a', 2));
} */
