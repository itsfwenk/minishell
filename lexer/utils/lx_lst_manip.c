/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_lst_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:36:03 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/24 10:24:32 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	define_subshell(char *str, int *i, t_token *ntoken,
	t_skibidi *skibidishell)
{
	char	*trimmed_par;

	trimmed_par = trim_parentheses(str, i);
	if (trimmed_par == NULL)
		ft_free_clean(skibidishell);
	ntoken->sub_shell = ft_lexer(trimmed_par, skibidishell);
	free(trimmed_par);
}

t_token	*lx_meta_token(char *str, int *i, int token_type,
	t_skibidi *skibidishell)
{
	t_token	*ntoken;

	ntoken = ft_calloc(1, sizeof(t_token));
	if (ntoken == NULL)
		ft_free_clean(skibidishell);
	if (token_type >= PIPE && token_type <= OUT_REDIR)
		i[1] = i[0];
	if (token_type >= OR && token_type <= HERE_DOC)
		i[1] = i[0] + 1;
	ntoken->tstring = ft_calloc(1, sizeof(t_string));
	if (ntoken->tstring == NULL)
		ft_free_clean(skibidishell);
	ntoken->tstring->str = lx_strdup(str, i);
	if (ntoken->tstring->str == NULL)
		ft_free_clean(skibidishell);
	ntoken->full_string = lx_strictstrdup(str, i);
	if (ntoken->full_string == NULL)
		ft_free_clean(skibidishell);
	ntoken->type = token_type;
	i[0] = i[1] + 1;
	return (ntoken);
}

static void	set_end_index(char *str, int start, int end, int *i)
{
	if (str[start] == '\"' || str[start] == '\'')
	{
		while (str[end] != str[start])
		{
			end++;
		}
		dprintf(2, "start = %d\n", start);
		dprintf(2, "end = %d = %c\n", end, str[end]);
		i[1] = end + 1;
		dprintf(2, "i[1]= %d\n", i[1]);
		set_end_index(str, end + 1, end + 2, i);
		// dprintf(2, "start = %d\n", start);
		// dprintf(2, "end = %d = %c\n", end, str[end]);
	}
}

t_token	*lx_str_token(t_skibidi *skibidishell, char *str, int *i,
	int token_type)
{
	t_token	*ntoken;

	ntoken = ft_calloc(1, sizeof(t_token));
	if (ntoken == NULL)
		ft_free_clean(skibidishell);
	if (token_type == PAR_STR)
		to_close_parenthesis(str, i);
	else
	{
		set_end_index(str, i[0], i[1], i);
		while (is_word_delimiter(&skibidishell->tokens, str, i) == FALSE)
			i[1] = i[1] + 1;
		i[1] = i[1] - 1;
	}
	ntoken->tstring = create_tstring(str, i, token_type);
	if (ntoken->tstring == NULL)
		ft_free_clean(skibidishell);
	ntoken->full_string = lx_strictstrdup(str, i);
	if (ntoken->full_string == NULL)
		ft_free_clean(skibidishell);
	ntoken->type = token_type;
	if (token_type == PAR_STR)
		define_subshell(str, i, ntoken, skibidishell);
	i[0] = i[1] + 1;
	// dprintf(2, "TOKEN CREATED IS <%s>\n", ntoken->full_string);
	return (ntoken);
}
