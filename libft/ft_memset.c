/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:09:52 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/21 17:12:35 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	t_byte			*cast_s;
	unsigned char	cast_c;

	i = 0;
	cast_c = (unsigned char)c;
	cast_s = (t_byte *)s;
	while (i < n)
	{
		cast_s[i] = cast_c;
		i++;
	}
	return (s);
}
