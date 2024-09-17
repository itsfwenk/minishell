/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:08:07 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/17 15:37:08 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lexer(char *input, t_skibidi *skibidishell)
{
	int		i[2];
	t_token	*tokens;

	if (input == NULL || input[0] == '\0')
		return (NULL);
	ft_bzero(i, 2 * sizeof(int));
	tokens = NULL;
	while (input[i[0]] != '\0')
	{
		while (input[i[0]] != '\0'
			&& (input[i[0]] == ' ' || input[i[0]] == '\t'))
		{
			i[0] = i[0] + 1;
		}
		if (i[0] >= (int)ft_strlen(input))
			break ;
		i[1] = i[0] + 1;
		if (lx_createadd(&tokens, skibidishell, input, i) == FALSE)
			return (NULL);
		i[0] = i[1] + 1;
	}
	return (tokens);
}

void	merge_tokens(t_skibidi *skibidishell, t_token **token, t_token *cmd)
{
	t_token	*current;

	current = NULL;
	if (!token || *token == NULL)
		return ;
	if (*token && (*token)->type == PAR_STR)
	{
		merge_tokens(skibidishell, &(*token)->next, *token);
		merge_tokens(skibidishell, &(*token)->sub_shell, NULL);
	}
	current = *token;
	if (cmd == NULL)
		cmd = get_cmd(*token);
	if (current == cmd)
		current = current->next;
	merge_operators(skibidishell, current);
	merge_redirection(skibidishell, current, cmd);
	merge_arguments(skibidishell, current, cmd);
	if (skibidishell->tokens->type != PAR_STR && cmd != NULL)
		skibidishell->tokens = cmd;
}
