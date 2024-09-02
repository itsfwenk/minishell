/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:46:21 by fli               #+#    #+#             */
/*   Updated: 2024/09/02 16:10:02 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmd_limiter(t_token *token)
{
	if (token == NULL
		|| token->type == PIPE
		|| token->type == OR
		|| token->type == AND)
		return (TRUE);
	else
		return (FALSE);
}


void	add_new_leaf(t_leaf *leaves, t_token *start_token)
{
	int		n_tokens;
	t_token	*current;
	t_leaf	*new_leaf;

	n_tokens = 0;
	current = start_token;
	while (is_cmd_limiter(current) == FALSE)
	{
		n_tokens++;
	}
	new_leaf = malloc(sizeof(t_leaf));
	if (new_leaf == NULL)
	{
		return ; // ft_clean
	}
	new_leaf->n_tokens = n_tokens;
	get_input();
	get_output();
	get_cmd_args();
	get_left();
	get_right();
}

t_leaf	*create_leaves(t_token *tokens)
{
	t_token	*current_token;
	t_leaf	*leaves;

	current_token = tokens;
	while (current_token != NULL)
	{
		add_new_leaf(leaves, current_token);
	}
}
