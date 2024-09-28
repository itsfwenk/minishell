/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:37:33 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 16:37:54 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

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
