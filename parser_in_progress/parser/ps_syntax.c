/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:05:41 by fli               #+#    #+#             */
/*   Updated: 2024/08/29 20:14:41 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_syntax2(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == PIPE)
		{
			if (current->next->type != STR || current->next->type != PAR_STR)
				return (FALSE);
			return (TRUE);
		}
		if (current->type == IN_REDIR)
		{
			if (current->next->type != FILENAME)
				return (FALSE);
			return (TRUE);
		}
		if (current->type == OUT_REDIR)
		{
			if (current->next->type != FILENAME)
				return (FALSE);
			return (TRUE);
		}
	}
}

int	is_valid_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == PIPE)
		{
			if (current->next->type != STR || current->next->type != PAR_STR)
				return (FALSE);
		}
		if (current->type == IN_REDIR)
		{
			if (current->next->type != FILENAME)
				return (FALSE);
		}
		if (current->type == OUT_REDIR)
		{
			if (current->next->type != FILENAME)
				return (FALSE);
		}
		is_valid_syntax2(current);
	}
}
