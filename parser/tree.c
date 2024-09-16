/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:54:39 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/16 18:07:00 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_tree(t_token *token)
{
	t_token	*tree;
	t_token	*op;

	tree = token;
	while (token && token->next)
	{
		op = token->next;
		token = op->next;
		op->left = tree;
		op->right = token;
		tree = op;
	}
	return (tree);
}
