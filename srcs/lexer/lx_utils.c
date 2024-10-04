/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:21:01 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 17:27:37 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

int	is_sep(char *c)
{
	int		i;
	char	sep[12];

	ft_strlcpy(sep, "\"\'|<>()\t ", 12);
	i = 0;
	while (sep[i] != '\0')
	{
		if (c[0] == sep[i])
			return (true);
		i++;
	}
	if (c[0] == '$')
	{
		if (ft_isalpha(c[1]) != 0 || c[1] == '_')
			return (true);
	}
	if (c[0] == '&' && c[1] == '&')
		return (true);
	return (false);
}

static int	which_token2(char *c)
{
	if (c[0] == '|')
	{
		if (c[1] == '|')
			return (OR);
		else
			return (PIPE);
	}
	if (c[0] == '&' && c[1] == '&')
		return (AND);
	if (c[0] == '(')
		return (PAR_STR);
	return (STR);
}

int	which_token(t_token **tokens, char *c)
{
	t_token	*last_token;

	if (c[0] == '>')
	{
		if (c[1] == '>')
			return (APD_OUT_REDIR);
		return (OUT_REDIR);
	}
	if (c[0] == '<')
	{
		if (c[1] == '<')
			return (HERE_DOC);
		return (IN_REDIR);
	}
	last_token = lx_getlast(*tokens);
	if (last_token != NULL)
	{
		if (last_token->type == HERE_DOC)
			return (HD_LIMITER);
		if (last_token->type == IN_REDIR || last_token->type == OUT_REDIR
			|| last_token->type == APD_OUT_REDIR)
			return (FILENAME);
	}
	return (which_token2(c));
}
