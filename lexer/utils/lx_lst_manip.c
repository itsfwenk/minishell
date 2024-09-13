/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_lst_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:36:03 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/13 14:47:21 by mel-habi         ###   ########.fr       */
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
			return ; //ft_exit_clean
		ntoken->sub_shell = ft_lexer(trimmed_par);
		free(trimmed_par);
	}
	else
		ntoken->sub_shell = NULL;
}

t_token	*lx_meta_token(char *str, int *i, int token_type)
{
	t_token	*ntoken;

	ntoken = ft_calloc(1, sizeof(t_token));
	if (ntoken == NULL)
		return (NULL); // ft_exit_clean
	if (token_type >= PIPE && token_type <= OUT_REDIR)
		i[1] = i[0];
	if (token_type >= OR && token_type <= HERE_DOC)
		i[1] = i[0] + 1;
	ntoken->tstring = ft_calloc(1, sizeof(t_string));
	if (ntoken->tstring == NULL)
		return (NULL); // ft_exit_clean
	ntoken->tstring->str = lx_strdup(str, i);
	if (ntoken->tstring->str == NULL)
		return (NULL); // ft_exit_clean
	ntoken->full_string = lx_strictstrdup(str, i);
	if (ntoken->full_string == NULL)
		return (NULL); // ft_exit_clean
	ntoken->type = token_type;
	return (ntoken);
}

t_token	*lx_str_token(t_token **tokens, char *str, int *i, int token_type)
{
	t_token	*ntoken;

	ntoken = ft_calloc(1, sizeof(t_token));
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
	ntoken->tstring = create_tstring(str, i, token_type);
	if (ntoken->tstring == NULL)
		return (NULL); // ft_exit_clean
	ntoken->full_string = lx_strictstrdup(str, i);
	if (ntoken->full_string == NULL)
		return (NULL); // ft_exit_clean
	ntoken->type = token_type;
	define_subshell(token_type, str, i, ntoken);
	i[0] = i[1] + 1;
	return (ntoken);
}
