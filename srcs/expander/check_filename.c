/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:48:53 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 16:49:56 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static bool	is_literal(t_token *tokens, int i)
{
	int			j;
	int			k;
	t_string	*current;

	j = 0;
	current = tokens->tstring;
	while (current != NULL)
	{
		k = 0;
		while (current->str[k] != '\0')
		{
			if (j == i)
				return (current->between_quote == true);
			j++;
			k++;
		}
		current = tokens->tstring;
	}
	return (false);
}

bool	check_filename(t_token *tokens, char *filename, int i, int j)
{
	if (tokens->assembled[i] == '\0' && filename[j] == '\0')
		return (true);
	if (tokens->assembled[i] == '*' && !is_literal(tokens, i))
	{
		if (check_filename(tokens, filename, i + 1, j + 1) == true)
			return (true);
		return (check_filename(tokens, filename, i, j + 1));
	}
	if (tokens->assembled[i] == filename[j])
		return (check_filename(tokens, filename, i + 1, j + 1));
	return (false);
}
