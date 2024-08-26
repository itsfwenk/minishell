/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_lst_manip_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:10:11 by fli               #+#    #+#             */
/*   Updated: 2024/08/26 14:16:04 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*lx_strdup(char *str, int *i)
{
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
	while (start < end)
	{
		dup[start] = str[start];
		start++;
	}
	dup[start] = '\0';
	return (dup);
}
