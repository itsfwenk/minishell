/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_lst_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:12:59 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/07 10:38:06 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	define_subshell(t_skibidi *shell, char *str, int *i,
	t_token *ntoken)
{
	char	*trimmed_par;

	trimmed_par = trim_parentheses(str, i);
	if (trimmed_par == NULL)
		exit_shell(shell);
	ntoken->sub_shell = ft_lexer(shell, trimmed_par);
	free(trimmed_par);
}

t_token	*lx_meta_token(t_skibidi *shell, char *str, int *i, int token_type)
{
	t_token	*ntoken;

	ntoken = ft_calloc(1, sizeof(t_token));
	if (ntoken == NULL)
		exit_shell(shell);
	if (token_type >= PIPE && token_type <= OUT_REDIR)
		i[1] = i[0];
	if (token_type >= OR && token_type <= HERE_DOC)
		i[1] = i[0] + 1;
	ntoken->tstring = ft_calloc(1, sizeof(t_string));
	if (ntoken->tstring == NULL)
		exit_shell(shell);
	ntoken->tstring->str = lx_strdup(str, i);
	if (ntoken->tstring->str == NULL)
		exit_shell(shell);
	ntoken->full_string = lx_strictstrdup(str, i);
	if (ntoken->full_string == NULL)
		exit_shell(shell);
	ntoken->type = token_type;
	i[0] = i[1] + 1;
	return (ntoken);
}

static void	set_end_index(char *str, int start, int end, int *i)
{
	if (str[start] == '\"' || str[start] == '\'')
	{
		while (str[end] != str[start])
			end++;
		i[1] = end + 1;
		set_end_index(str, end + 1, end + 2, i);
	}
}

t_token	*lx_str_token(t_skibidi *shell, char *str, int *i,
	int token_type)
{
	t_token	*ntoken;

	ntoken = ft_calloc(1, sizeof(t_token));
	if (ntoken == NULL)
		exit_shell(shell);
	if (token_type == PAR_STR)
		to_close_parenthesis(str, i);
	else
	{
		set_end_index(str, i[0], i[1], i);
		while (is_word_delimiter(&shell->tokens, str, i) == false)
			i[1] = i[1] + 1;
		i[1] = i[1] - 1;
	}
	ntoken->tstring = create_tstring(str, i, token_type);
	if (ntoken->tstring == NULL)
		exit_shell(shell);
	ntoken->full_string = lx_strictstrdup(str, i);
	if (ntoken->full_string == NULL)
		exit_shell(shell);
	ntoken->type = token_type;
	if (token_type == PAR_STR)
		define_subshell(shell, str, i, ntoken);
	i[0] = i[1] + 1;
	return (ntoken);
}
