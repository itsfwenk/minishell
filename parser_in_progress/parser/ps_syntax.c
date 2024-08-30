/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:05:41 by fli               #+#    #+#             */
/*   Updated: 2024/08/30 19:19:02 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token *check_syntax2(t_token *current)
{
	if (current->type == HERE_DOC)
	{
		if (current->next->type != HD_LIMITER)
			return (current->next->type);
	}
	if (current->type == FILENAME || current->type == HD_LIMITER)
	{
		if (current->next->type < PIPE && current->next->type > STR)
			return(current->next->type);
	}
	if (current->type == STR)
	{
		if (current->next->type >= PAR_STR)
			return (current->next->type);
	}
	if (current->type == PAR_STR)
	{
		if (current->next->type >= STR)
			return (current->next->type);
	}
	return (NULL);
}

static t_token *check_syntax1(t_token *current)
{
	if (current->type == PIPE)
	{
		if (current->next->type != IN_REDIR
			&& current->next->type != OUT_REDIR
			&& current->next->type < APD_OUT_REDIR
			&& current->next->type > PAR_STR)
			return (current->next->type);
	}
	if (current->type == IN_REDIR || current->type == OUT_REDIR
		|| current->type == APD_OUT_REDIR)
	{
		if (current->next->type != FILENAME)
			return (current->next->type);
	}
	if (current->type == OR || current->type == AND)
	{
		if (current->next->type != STR && current->next->type != PAR_STR
			&& current->next->type != IN_REDIR
			&& current->next->type != OUT_REDIR
			&& current->next->type != APD_OUT_REDIR
			&& current->next->type != HERE_DOC)
			return (current->next->type);
	}
	return(check_syntax2(current));
}

void	check_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*error_token;

	current = tokens;
	while (current != NULL)
	{
		error_token = check_syntax1(current);
		if (error_token != NULL)
		{
			ft_print_error(NULL, , \
				"syntax error near unexpected token", "`'");
		}
	}
}
