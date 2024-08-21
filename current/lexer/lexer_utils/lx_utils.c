/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:14:00 by fli               #+#    #+#             */
/*   Updated: 2024/08/21 17:47:03 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static int	which_sep2(char *c)
{
	if (c[0] =='>')
	{
		if (c[1] == '>')
			return (APD_OUT_REDIR);
		else
			return (OUT_REDIR);
	}
	if (c[0] == '(')
		return (OPN_PAR);
	if (c[0] == ')')
		return (CLS_PAR);
	// if (c[0] == '$')
	// {
	// 	if (ft_isalpha(c[1]) != FALSE || c[1] == '_')
	// 		return (ENV_VAR);
	// }
	return (-1);
}

int	which_sep(char *c)
{
	if (c[0] == '\"')
		return (D_QUOTE);
	if (c[0] =='\'')
		return (S_QUOTE);
	if (c[0] == '|')
	{
		if (c[1] == '|')
			return (OR);
		else
			return (PIPE);
	}
	if (c[0] == '&' && c[1] == '&')
		return (AND);
	if (c[0] == '<')
	{
		if (c[1] == '<')
			return (HERE_DOC);
		else
			return (IN_REDIR);
	}
	return (which_sep2(c));
}
