/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manip_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:10:11 by fli               #+#    #+#             */
/*   Updated: 2024/08/20 14:37:54 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*lx_strdup(char *str, int i, int j)
{
	int		i;
	char	*dup;

	dup = malloc((j - i + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL); //ft_exit
	i = 0;
	while (i != j)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
