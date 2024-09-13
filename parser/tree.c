/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:54:39 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/13 19:47:20 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node *create_node(t_token *token, int ignored)
{
	t_node *node;

	if (ignored)
		return (NULL);
	node = ft_calloc(1, sizeof(t_node));
	if (node)
		node->value = token;
	return (node);
}

t_node *create_tree(t_token *token)
{
	t_node *tree;
	t_node *node;

	tree = NULL;
	while (token)
	{
		node = create_node(token->next, 0);
		if (!node)
			return (NULL);
		node->left = create_node(token, !!tree);
		if (!tree && !node->left)
			return (NULL);
		token = token->next;
		if (token)
		{
			token = token->next;
			node->right = create_node(token, 0);
			if (!node->right)
				return (NULL);
		}
		if (tree)
			node->left = tree;
		tree = node;
	}
	return (tree);
}
