/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:46:21 by fli               #+#    #+#             */
/*   Updated: 2024/08/29 20:14:44 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmd_limiter(t_token *current_tokens)
{
	if (current_tokens->type )
}


void	add_new_leaf(t_token *current_tokens)
{
	while (current_tokens->next )
}

t_leaf	*create_leaves(t_token *tokens)
{
	t_token	*current_token;
	t_leaf	*leaves;

	current_token = tokens;
	while (current_token != NULL)
	{
		add_new_leaf(current_token);
	}
}
