/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manip_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:10:11 by fli               #+#    #+#             */
/*   Updated: 2024/08/22 12:15:06 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*lx_strdup(char *str, int *i)
{
	int		i_dup;
	char	*dup;

	dup = malloc((i[1] - i[0] + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL); //ft_exit
	i_dup = i[0];
	while (i_dup != i[1])
	{
		dup[i_dup] = str[i_dup];
		i_dup++;
	}
	dup[i_dup] = '\0';
	return (dup);
}
