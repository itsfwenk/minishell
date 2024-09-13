/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:09:48 by fli               #+#    #+#             */
/*   Updated: 2024/09/13 13:27:01 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	check_key(char *key, int *limits)
// {
// 	size_t	i;

// 	i = 0;
// 	while (key[i] != ' ')
// 	{
// 		if (!i && !ft_isalpha(key[i]) && key[i] != '_')
// 			return (0);
// 		if (i && !ft_isalnum(key[i]) && key[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// void	expand_env_var(t_string *current)
// {
// 	int	i;

// 	i = 0;
// 	if (current->to_be_expanded == TRUE)
// 	{
// 		while (current->str[i] != '\0')
// 		{
// 			if (current->str[i] == '$')
// 			{
// 				if (ft_isdigit(current->str[i + 1]) != FALSE)
// 					exp_positional_param(current, &i);
// 			}
// 		}
// 	}
// }

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
			exp_special_char(current_tstr);
			exp_pos_param(current_tstr);
			if (exp_env_var(current_tstr, skibidishell) == FALSE)
				return (FALSE); // ft_clean token etc..
		}
		current_tstr = current_tstr->next;
	}
	ft_expander(skibidishell, token->arguments);
	ft_expander(skibidishell, token->infile);
	ft_expander(skibidishell, token->outfile);
	ft_expander(skibidishell, token->sub_shell);
}
