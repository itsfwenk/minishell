/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:21:31 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/23 19:54:22 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_literal(t_token *tokens, int i)
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
				return (current->between_quote == TRUE);
			j++;
			k++;
		}
		current = tokens->tstring;
	}
	return (FALSE);
}

int	check_filename(t_token *tokens, char *filename, int i, int j)
{
	dprintf(2, "i = %d j = %d\n", i , j);
	if (tokens->assembled[i] == '\0' && filename[j] == '\0')
		return (TRUE);
	if (tokens->assembled[i] == '*' && !is_literal(tokens, i))
	{
		if (check_filename(tokens, filename, i + 1, j) == TRUE)
			return (TRUE);
		return (check_filename(tokens, filename, i, j + 1));
	}
	if (tokens->assembled[i] == filename[j])
		return (check_filename(tokens, filename, i + 1, j + 1));
	return (FALSE);
}
