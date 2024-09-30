/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_tstring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:46:38 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/30 14:04:53 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static size_t	get_full_len(t_token *current)
{
	size_t		full_len;
	t_string	*tstring;

	full_len = 0;
	tstring = current->tstring;
	while (tstring != NULL && tstring->str != NULL)
	{
		full_len = full_len + ft_strlen(tstring->str);
		tstring = tstring->next;
	}
	return (full_len);
}

static void	cat_tstring(t_token *current, char *assembled, int	*i)
{
	int			j;
	t_string	*current_tstring;

	current_tstring = current->tstring;
	while (current_tstring != NULL)
	{
		j = 0;
		while (current_tstring->str[j] != '\0')
		{
			assembled[*i] = current_tstring->str[j];
			(*i)++;
			j++;
		}
		current_tstring = current_tstring->next;
	}
	assembled[*i] = '\0';
}

void	assemble_tstring(t_skibidi *shell, t_token *token)
{
	int		i;
	char	*assembled;
	t_token	*current;

	if (token == NULL)
		return ;
	i = 0;
	assembled = ft_calloc(get_full_len(token) + 1, sizeof(char));
	if (assembled == NULL)
		exit_shell(shell);
	cat_tstring(token, assembled, &i);
	token->assembled = assembled;
	current = token->arguments;
	while (current)
	{
		assemble_tstring(shell, current);
		current = current->next;
	}
	current = token->redir;
	while (current)
	{
		assemble_tstring(shell, current);
		current = current->next;
	}
}
