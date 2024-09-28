/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:58:58 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/27 17:00:19 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

bool	in_charset(char c, char *charset)
{
	size_t	i;

	i = 0;
	if (!charset)
		return (false);
	while (charset[i])
	{
		if (c == charset[i])
			return (true);
		i++;
	}
	return (false);
}

bool	is_space(char c)
{
	return (in_charset(c, " \t"));
}

bool	is_meta(char c)
{
	return (in_charset(c, "|&<>"));
}

char	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (c);
	return ('\0');
}
