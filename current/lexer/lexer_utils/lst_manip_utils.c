/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manip_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:10:11 by fli               #+#    #+#             */
/*   Updated: 2024/08/25 16:17:17 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*lx_strdup(char *str, int *i)
{
	int		start;
	int		end;
	char	*dup;

	if (str[i[0]] == '\'' || str[i[0]] == '"')
	{
		start = i[0] + 1;
		end = i[1] - 1;
	}
	else
	{
		start = i[0];
		end = i[1];
	}
	dup = malloc((end - start + 2) * sizeof(char));
	if (dup == NULL)
		return (NULL); //ft_exit
	while (start <= end)
	{
		dup[start] = str[start];
		start++;
	}
	dup[start] = '\0';
	return (dup);
}
