/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tstring_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:27:27 by fli               #+#    #+#             */
/*   Updated: 2024/08/27 17:03:47 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

	last = lx_getlast(*tstring);
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
