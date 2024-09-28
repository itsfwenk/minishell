/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tstring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:29:12 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 18:04:12 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

void	q_tstr(char *str, int *i, t_string **tstring)
{
	int			limits[2];
	t_string	*new_tstring;

	new_tstring = ft_calloc(1, sizeof(t_string));
	if (new_tstring == NULL)
		return ;
	limits[0] = i[0];
	limits[1] = limits[0] + 1;
	while (str[limits[1]] != str[i[0]])
		limits[1]++;
	new_tstring->str = lx_strdup(str, limits);
	new_tstring->to_be_expanded = str[i[0]] == '"';
	new_tstring->between_quote = true;
	i[0] = limits[1] + 1;
	tstring_addback(tstring, new_tstring);
}

static void	set_limits(char *str, int *limits, int *i)
{
	limits[0] = i[0];
	limits[1] = i[0] + 1;
	if (str[limits[0]] == '(')
	{
		limits[1] = i[1];
		return ;
	}
	while (limits[1] <= i[1])
	{
		if (str[limits[1]] == '\'' || str[limits[1]] == '"')
		{
			limits[1]--;
			break ;
		}
		limits[1]++;
	}
	if (str[limits[1]] == ' ')
		limits[1] = limits[1] - 1;
}

void	other_tstr(char *str, int *i, int token_type, t_string **tstring)
{
	int			limits[2];
	t_string	*new_tstring;

	new_tstring = ft_calloc(1, sizeof(t_string));
	if (new_tstring == NULL)
		return ;
	set_limits(str, limits, i);
	new_tstring->str = lx_strdup(str, limits);
	new_tstring->to_be_expanded = true;
	if (token_type == HD_LIMITER)
		new_tstring->to_be_expanded = false;
	new_tstring->between_quote = false;
	if (str[i[0]] == '"')
		new_tstring->between_quote = true;
	i[0] = limits[1] + 1;
	tstring_addback(tstring, new_tstring);
}

t_string	*create_tstring(char *str, int *i, int token_type)
{
	int			start;
	int			end;
	t_string	*tstring;

	start = i[0];
	end = i[1];
	tstring = NULL;
	while (i[0] <= i[1])
	{
		if (str[i[0]] == '\'' || str[i[0]] == '"')
			q_tstr(str, i, &tstring);
		else
			other_tstr(str, i, token_type, &tstring);
	}
	i[0] = start;
	return (tstring);
}
