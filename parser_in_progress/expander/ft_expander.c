/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:09:48 by fli               #+#    #+#             */
/*   Updated: 2024/09/02 19:39:58 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exp_check_key(char *key)
{
	size_t	i;

	i = 0;
	while (key[i] != ' ')
	{
		if (!i && !ft_isalpha(key[i]) && key[i] != '_')
			return (0);
		if (i && !ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	expand_env_var(t_string *current)
{
	int	i;

	i = 0;
	if (current->to_be_expanded == TRUE)
	{
		while (current->str[i] != '\0')
		{
			if (current->str[i] == '$')
			{

			}
		}
	}
}

void	ft_expander(t_string *tstring)
{
	t_string	*current;

	current = tstring;
	while (current != NULL)
	{

	}
}
