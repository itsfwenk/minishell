/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:49:50 by fli               #+#    #+#             */
/*   Updated: 2024/08/30 20:00:02 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_quotes(t_string *tstring)
{
	int		tot;
	char	*quoted;

	quoted = malloc((ft_strlen(tstring->str) + 3) * sizeof(char));
	if (quoted == NULL)
		return (NULL);
	if (tstring->between_quote == TRUE)
	{
		if (tstring->to_be_expanded == TRUE)
		{
			quoted[0] = '"';
			quoted[ft_strlen(tstring->str) + 1] = '"';
		}
		else
		{
			quoted[0] = '\'';
			quoted[ft_strlen(tstring->str) + 1] = '\'';
		}
	}
	ft_strlcpy(&quoted[1], tstring->str, ft_strlen(tstring->str));
	quoted[ft_strlen(tstring->str) + 2] = '\0';
	return (quoted);
}

char	*reconstruct_str(t_token token)
{
	char		*full_str;
	char		*to_free;
	char		*to_add;
	t_string	*tstring;

	tstring = token.tstring;
	full_str = add_quotes(tstring);
	if (full_str == NULL)
		return (NULL); //ft_exit_clean
	while (tstring->next != NULL)
	{
		tstring = tstring->next;

		str1 = add_quotes(tstring->next);
		str2 = add_quotes(tstring->next);
		full_str = ft_strjoin()
	}











		if (tstring->to_be_expanded == TRUE)
		{
			to_free = ft_strjoin("\"", tstring->str);
			if (to_free == NULL)
				return (NULL); //ft_exit_clean
			full_str = ft_strjoin(to_free, "\"");
		}
	}
	full_str = ft_strdup(tstring->str);
	while (tstring->next != NULL)
	{
		to_free = full_str;
		full_str = ft_strjoin(full_str, tstring->next->str);
		free(to_free);
		tstring = tstring->next;
	}
}
