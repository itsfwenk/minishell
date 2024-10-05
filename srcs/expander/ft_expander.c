/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:04:18 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/05 11:54:15 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static bool	expand_arg_redir(t_skibidi *shell, t_token *token)
{
	t_token	*current;

	current = token->arguments;
	while (current)
	{
		if (ft_expander(shell, current) == false)
			return (false);
		current = current->next;
	}
	current = token->redir;
	while (current)
	{
		if (ft_expander(shell, current) == false)
			return (false);
		current = current->next;
	}
	return (true);
}

bool	ft_expander(t_skibidi *shell, t_token *token)
{
	t_string	*current_tstr;

	if (token == NULL)
		return (true);
	current_tstr = token->tstring;
	while (current_tstr != NULL)
	{
		if (current_tstr->to_be_expanded == true)
		{
			if (current_tstr->str[0] == '$' && current_tstr->str[1] == '\0'
				&& current_tstr->next)
				current_tstr->str[0] = '\0';
			current_tstr->str = exp_pos_param(shell, current_tstr->str);
			current_tstr->str = exp_env_var(shell, current_tstr->str);
			if (current_tstr->str == NULL)
			{
				shell->exit_code = 1;
				return (false);
			}
		}
		current_tstr = current_tstr->next;
	}
	return (expand_arg_redir(shell, token));
}
