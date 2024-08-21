/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:11:15 by fli               #+#    #+#             */
/*   Updated: 2024/05/23 14:04:41 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*cal;

	if (nmemb * size < size && nmemb * size != 0)
		return (NULL);
	cal = malloc(nmemb * size);
	if (cal == NULL)
		return (NULL);
	ft_bzero(cal, nmemb * size);
	return (cal);
}
