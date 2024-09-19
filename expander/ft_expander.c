/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:09:48 by fli               #+#    #+#             */
/*   Updated: 2024/09/19 10:26:13 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expander(t_skibidi *skibidishell, t_token *token)
{
	t_string	*current_tstr;

	if (token == NULL)
		return ;
	current_tstr = token->tstring;
	while (current_tstr != NULL)
	{
		if (current_tstr->to_be_expanded == TRUE)
		{
			exp_pos_param(current_tstr, skibidishell);
			if (exp_env_var(current_tstr, skibidishell) == FALSE)
				return ;
		}
		current_tstr = current_tstr->next;
	}
	ft_expander(skibidishell, token->arguments);
	ft_expander(skibidishell, token->redir);
	// ft_expander(skibidishell, token->sub_shell);
}
