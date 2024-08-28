/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_lst_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:36:03 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/28 15:01:18 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	define_subshell(int token_type, char *str, int *i, t_token *ntoken)
{
	char	*trimmed_par;

	if (token_type == PAR_STR)
	{
		trimmed_par = trim_parentheses(str, i);
		if (trimmed_par == NULL)
			return (NULL); //ft_exit_clean
		ntoken->sub_shell = ft_lexer(trim_parentheses);
		free(trimmed_par);
	}
	else
		ntoken->sub_shell = NULL;
}

t_token	*lx_meta_token(char *str, int *i, int token_type)
{
	t_token	*ntoken;

	ntoken = malloc(sizeof(t_token));
	if (ntoken == NULL)
		return (NULL); // ft_exit_clean
	if (token_type >= PIPE && token_type <= OUT_REDIR)
		i[1] = i[0];
	if (token_type >= OR && token_type <= HERE_DOC)
		i[1] = i[0] + 1;
	ntoken->tstring = malloc(sizeof(t_string));
	if (ntoken->tstring == NULL)
		return (NULL); // ft_exit_clean
	ntoken->tstring->str = lx_strdup(str, i);
	if (ntoken->tstring->str == NULL)
		return (NULL); // ft_exit_clean
	ntoken->tstring->to_be_expanded = FALSE;
	ntoken->tstring->between_quote = FALSE;
	ntoken->tstring->next = NULL;
	ntoken->type = token_type;
	ntoken->sub_shell = NULL;
	ntoken->next = NULL;
	return (ntoken);
}

t_token	*lx_str_token(t_token **tokens, char *str, int *i, int token_type)
{
	t_token	*ntoken;

	ntoken = malloc(sizeof(t_token));
	if (ntoken == NULL)
		return (NULL); // ft_exit_clean
	if (token_type == PAR_STR)
		to_close_parenthesis(str, i);
	else
	{
		while (is_word_delimiter(tokens, str, i[1]) == FALSE)
			i[1] = i[1] + 1;
		i[1] = i[1] - 1;
	}
	ntoken->tstring = create_tstring(tokens, str, i, token_type);
	if (ntoken->tstring == NULL)
		return (NULL); // ft_exit_clean
	ntoken->type = token_type;
	define_subshell(token_type, str, i, ntoken);
	ntoken->next = NULL;
	i[0] = i[1] + 1;
	return (ntoken);
}
