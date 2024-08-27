/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:14:00 by fli               #+#    #+#             */
/*   Updated: 2024/08/27 10:59:02 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_sep(char *c)
{
	int		i;
	char	sep[12];

	ft_strlcpy(sep, "\"\'|<>()\t ", 12);
	i = 0;
	while (sep[i] != '\0')
	{
		if (c[0] == sep[i])
			return (TRUE);
		i++;
	}
	if (c[0] == '$')
	{
		if (ft_isalpha(c[1]) != 0 || c[1] == '_')
			return (TRUE);
	}
	if (c[0] == '&' && c[1] == '&')
		return (TRUE);
	return (FALSE);
}

static int	which_token3(t_token **tokens, char *c)
{
	t_token	*last_token;

	last_token = lx_getlast(*tokens);
	if (last_token == NULL)
		return (STR);
	if (last_token->type == HERE_DOC)
		return (HD_LIMITER);
	if (last_token->type == IN_REDIR || last_token->type == OUT_REDIR
		|| last_token->type == APD_OUT_REDIR)
		return (FILENAME);
	return (STR);
}

static int	which_token2(t_token **tokens, char *c)
{
	if (c[0] == '"')
		return (STR);
	if (c[0] == '\'')
		return (STR);
	if (c[0] == '(')
		return (PAR_STR);
	return (which_token3(tokens, c));
}

int	which_token(t_token **tokens, char *c)
{
	if (c[0] == '|')
	{
		if (c[1] == '|')
			return (OR);
		else
			return (PIPE);
	}
	if (c[0] =='>')
	{
		if (c[1] == '>')
			return (APD_OUT_REDIR);
		else
			return (OUT_REDIR);
	}
	if (c[0] == '<')
	{
		if (c[1] == '<')
			return (HERE_DOC);
		else
			return (IN_REDIR);
	}
	if (c[0] == '&' && c[1] == '&')
		return (AND);
	return (which_token2(tokens, c));
}
