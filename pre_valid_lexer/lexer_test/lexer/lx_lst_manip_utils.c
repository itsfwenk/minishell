/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_lst_manip_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:10:11 by fli               #+#    #+#             */
/*   Updated: 2024/08/27 16:47:54 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*lx_strdup(char *str, int *i)
{
	int		j;
	int		start;
	int		end;
	int		truelen;
	char	*dup;

	if (str[i[0]] == '\'' || str[i[0]] == '"')
		truelen = i[1] - i[0] - 1;
	else
		truelen = i[1] - i[0] + 1;
	dup = malloc((truelen + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL); //ft_exit
	start = i[0];
	if (str[i[0]] == '\'' || str[i[0]] == '"')
		start = i[0] + 1;
	end = start + truelen;
	j = 0;
	while (start < end)
	{
		dup[j] = str[start];
		j++;
		start++;
	}
	dup[truelen] = '\0';
	return (dup);
}
