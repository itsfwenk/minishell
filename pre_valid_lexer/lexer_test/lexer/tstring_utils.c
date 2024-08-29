/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tstring_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:27:27 by fli               #+#    #+#             */
/*   Updated: 2024/08/27 17:04:20 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_string	*tstring_getlast(t_string *tstring)
{
	t_string	*current;

	current = tstring;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

void	tstring_addback(t_string **tstring, t_string *new_tstring)
{
	t_string	*last;

	last = tstring_getlast(*tstring);
	if (last == NULL)
		*tstring = new_tstring;
	else
		last->next = new_tstring;
}

void	tstring_del(t_string **tstring)
{
	t_string	*current;
	t_string	*previous;

	current = *tstring;
	while (current != NULL)
	{
		free(current->str);
		previous = current;
		current = current->next;
		free(previous);
	}
}
