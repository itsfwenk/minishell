/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:35:43 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/23 23:46:51 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	abs_int(int n)
{
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	return (nb);
}

static size_t	count_size(int n)
{
	size_t			size;
	unsigned int	nb;

	size = 0;
	if (n <= 0)
		size++;
	nb = abs_int(n);
	while (nb)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

static void	fill_str(char *str, int n, size_t size)
{
	size_t			i;
	unsigned int	nb;	

	i = 0;
	nb = abs_int(n);
	while (i < size)
	{
		str[size - 1 - i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	if (n < 0)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*result;

	size = count_size(n);
	result = (char *)ft_calloc(size + 1, sizeof(char));
	if (result)
	{
		if (!n)
			result[0] = '0';
		else
			fill_str(result, n, size);
	}
	return (result);
}
