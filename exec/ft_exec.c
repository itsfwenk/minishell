/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:41:07 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/17 17:02:21 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_tree(t_token *tree)
{
	if (!tree)
		return ;
	exec_tree(tree->left);
	ft_dprintf(2, "%s %s %s\n", tree->left->full_string, tree->full_string, tree->right->full_string);
	exec_tree(tree->right);
}


int	ft_exec(t_skibidi *skibidishell)
{
	t_token	*tree;

	tree = skibidishell->tree;
}
