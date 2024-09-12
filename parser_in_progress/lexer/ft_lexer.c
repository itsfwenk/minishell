/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:08:07 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/12 18:36:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lexer(char *input)
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
		if (lx_createadd(&tokens, input, i) == FALSE)
			return (NULL); // ft_exit_clean
		i[0] = i[1] + 1;
	}
	return (tokens);
}

static int	is_in_redirection(t_token *token)
{
	if (token->type == IN_REDIR || token->type == HERE_DOC)
		return (TRUE);
	return (FALSE);
}

static int	is_in_redirection(t_token *token)
{
	if (token->type == OUT_REDIR || token->type == APD_OUT_REDIR)
		return (TRUE);
	return (FALSE);
}

static int	is_operator(t_token *token)
{
	if (token->type == PIPE || token->type == OR || token->type == AND)
		return (TRUE);
	return (FALSE);
}

t_token	*get_cmd(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->type == STR)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	merge_redirection(t_token *current, t_token *cmd)
{
	t_token	*new_start;

	if (current && is_in_redirection(current))
	{
		lx_addback(&(cmd->infile), current);
		new_start = current->next->next;
		if (new_start == cmd)
			new_start = cmd->next;
		current->next->next = NULL;
		merge_tokens(new_start, cmd);
	}
	if (current && is_out_redirection(current->next))
	{
		lx_addback(&(cmd->outfile), current);
		new_start = current->next->next;
		if (new_start == cmd)
			new_start = cmd->next;
		current->next->next = NULL;
		merge_tokens(new_start, cmd);
	}
}
void	merge_tokens(t_token **token, t_token *cmd)
{
	t_token	*current;

	if (*token == NULL)
		return ;
	if ((*token)->type == PAR_STR)
		merge_tokens((*token)->sub_shell, NULL);
	current = token;
	if (cmd == NULL)
		cmd = get_cmd(*token);
	if (current == cmd)
		current = current->next;
	if (current && is_operator)
		merge_tokens(current->next, NULL);
	merge_redirection(current, cmd);
	*token = cmd;
}
