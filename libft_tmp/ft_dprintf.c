/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:30:22 by fli               #+#    #+#             */
/*   Updated: 2024/09/24 01:28:57 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

static void	ft_dprintf_c(va_list arg_ptr, int *count, int fd)
{
	char	c;

	c = va_arg(arg_ptr, int);
	ft_putchar_fd(c, fd);
	*count = *count + 1;
}

static void	ft_dprintf_s(va_list arg_ptr, int *count, int fd)
{
	char	*s;

	s = va_arg(arg_ptr, char *);
	if (s == NULL)
	{
		ft_putstr_fd("(null)", fd);
		*count = *count + 6;
		return ;
	}
	ft_putstr_fd(s, fd);
	*count = *count + ft_strlen(s);
}

static void	ft_putformat(const char format, va_list args, int fd, int *count)
{
	if (format == 'c')
		return (ft_dprintf_c(args, count, fd));
	else if (format == 's')
		return (ft_dprintf_s(args, count, fd));
	return ;
}

int	ft_dprintf(int fd, const char *entry, ...)
{
	int		i;
	int		count;
	va_list	arg_ptr;

	if (entry == NULL)
		return (-1);
	va_start(arg_ptr, entry);
	i = 0;
	count = 0;
	while (entry[i] != '\0')
	{
		if (entry[i] == '%')
		{
			ft_putformat(entry[i + 1], arg_ptr, fd, &count);
			i++;
		}
		else
		{
			ft_putchar_fd(entry[i], fd);
			count = count + 1;
		}
		i++;
	}
	va_end(arg_ptr);
	return (count);
}
