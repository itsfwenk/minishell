/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tstring_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:28:16 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 16:28:34 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

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

int	tstring_size(t_string **tstring)
{
	int			i;
	t_string	*current;

	i = 0;
	current = *tstring;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}
