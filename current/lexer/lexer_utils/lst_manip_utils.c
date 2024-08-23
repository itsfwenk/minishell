/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manip_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:10:11 by fli               #+#    #+#             */
/*   Updated: 2024/08/23 17:55:31 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_truelen(char *str, int *i, int token_type)
{
	int	i_dup;
	int	in_quote;


	i = i[0];

}

char	*lx_strdup(char *str, int *i, int token_type)
{
	int		i_dup;
	int		truelen;
	char	*dup;

	truelen = get_truelen(str, i, token_type);
	dup = malloc(truelen * sizeof(char));
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
