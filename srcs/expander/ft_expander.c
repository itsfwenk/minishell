/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:04:18 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 18:04:12 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	expand_arg_redir(t_skibidi *shell, t_token *token)
{
	t_token	*current;

	current = token->arguments;
	while (current)
	{
		ft_expander(shell, current);
		current = current->next;
	}
	current = token->redir;
	while (current)
	{
		ft_expander(shell, current);
		current = current->next;
	}
}

void	ft_expander(t_skibidi *shell, t_token *token)
{
	t_string	*current_tstr;
	t_token		*current;

	if (token == NULL)
		return ;
	current_tstr = token->tstring;
	while (current_tstr != NULL)
	{
		if (current_tstr->to_be_expanded == true)
		{
			exp_pos_param(shell, current_tstr->str);
			if (exp_env_var(shell, current_tstr->str) == false)
				return ;
		}
		current_tstr = current_tstr->next;
	}
	expand_arg_redir(shell, token);
}
