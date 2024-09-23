/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tstring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:58:42 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/23 17:18:35 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		limits[1]++;
	}
	new_tstring->str = lx_strdup(str, limits);
	new_tstring->to_be_expanded = str[i[0]] == '"';
	new_tstring->between_quote = TRUE;
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
	// while (str[limits[0]] == '"' && str[limits[1]] != '"')
	// {
	// 	limits[1]++;
	// }
	while (limits[1] < i[1])
	{
		if (str[limits[1]] == '\'' || str[limits[1]] == '"')
		{
			limits[1]--;
			break ;
		}
		limits[1]++;
	}
	// limits[1] = limits[1] - 2;
}

void	other_tstr(char *str, int *i, int token_type, t_string **tstring)
{
	int			limits[2];
	t_string	*new_tstring;

	new_tstring = ft_calloc(1, sizeof(t_string));
	if (new_tstring == NULL)
		return ;
	set_limits(str, limits, i);
	dprintf(2, "limits[0] in  other_tstr %d\n", limits[0]);
	dprintf(2, "limits[1] in  other_tstr %d\n", limits[1]);
	new_tstring->str = lx_strdup(str, limits);
	new_tstring->to_be_expanded = TRUE;
	if (token_type == HD_LIMITER)
		new_tstring->to_be_expanded = FALSE;
	new_tstring->between_quote = FALSE;
	if (str[i[0]] == '"')
		new_tstring->between_quote = TRUE;
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
	dprintf(2, "start in  create_tstring %d\n", start);
	dprintf(2, "end in  create_tstring %d\n", end);
	tstring = NULL;
	while (i[0] <= i[1])
	{
		if (str[i[0]] == '\'' || str[i[0]] == '"')
			q_tstr(str, i, &tstring);
		else
			other_tstr(str, i, token_type, &tstring);
		dprintf(2, "i[0] in loop %d\n", i[0]);
		dprintf(2, "i[1] in loop %d\n", i[1]);
	}
	i[0] = start;
	// i[1] = end;
	dprintf(2, "i[0] in  create_tstring %d\n", i[0]);
	dprintf(2, "i[1] in  create_tstring %d\n", i[1]);
	return (tstring);
}
