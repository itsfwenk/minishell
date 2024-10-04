/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:30:57 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 11:38:26 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static t_token	*check_syntax2(t_token *current)
{
	if (current->type == HERE_DOC)
	{
		if (current->next == NULL || current->next->type != HD_LIMITER)
			return (current->next);
	}
	if (current->type == FILENAME || current->type == HD_LIMITER)
	{
		if (current->next && current->next->type == PAR_STR)
			return (current->next);
	}
	if (current->type == STR)
	{
		if (current->next && current->next->type >= PAR_STR)
			return (current->next);
	}
	if (current->type == PAR_STR)
	{
		if (!current->sub_shell)
			return (current);
		if (current->next && current->next->type >= STR)
			return (current->next);
	}
	return (NULL);
}

static t_token	*check_syntax1(t_token *current)
{
	if (current->type == PIPE || current->type == OR || current->type == AND)
	{
		if (current->next == NULL
			|| (current->next->type == PIPE
				|| current->next->type == OR
				|| current->next->type == AND))
			return (current->next);
	}
	if (current->type == IN_REDIR || current->type == OUT_REDIR
		|| current->type == APD_OUT_REDIR)
	{
		if (current->next == NULL || current->next->type != FILENAME)
			return (current->next);
	}
	return (check_syntax2(current));
}

static int	check_first(t_token *first_token)
{
	if (!first_token)
		return (false);
	if (first_token->type == PIPE
		|| first_token->type == OR
		|| first_token->type == AND)
	{
		ft_print_error(NULL, first_token->full_string, \
				"syntax error near unexpected token", "`'");
		return (2);
	}
	return (true);
}

static void	print_syntax_error(t_token *error_token)
{
	if (!error_token)
		return ;
	if (error_token->type != PAR_STR)
	{
		ft_print_error(NULL, error_token->full_string, \
		"syntax error near unexpected token", "`'");
	}
	else
	{
		ft_print_error(NULL, "(", \
		"syntax error near unexpected token", "`'");
	}
	return ;
}

bool	check_syntax(t_skibidi *shell, t_token *tokens)
{
	t_token	*current;
	t_token	*error_token;

	current = tokens;
	if (check_first(current) == 2)
	{
		shell->exit_code = 2;
		return (false);
	}
	while (current != NULL)
	{
		error_token = check_syntax1(current);
		if (error_token != NULL)
		{
			shell->exit_code = 2;
			print_syntax_error(error_token);
			return (false);
		}
		current = current->next;
	}
	return (true);
}
