/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_tstring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:42:41 by fli               #+#    #+#             */
/*   Updated: 2024/09/11 11:40:53 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_asterisks(t_token *current)
{
	int			i;
	int			asterisk;
	t_string	*tstring;

	i = 0;
	asterisk = 0;
	tstring = current->tstring;
	while (tstring != NULL)
	{
		while (tstring->str)
		asterisk = asterisk + ft_strlen(tstring->str);
		tstring = tstring->next;
	}
	return (asterisk);
}

int	get_full_len(t_token *current)
{
	int			full_len;
	t_string	*tstring;

	full_len = 0;
	tstring = current->tstring;
	while (tstring != NULL)
	{
		full_len = full_len + ft_strlen(tstring->str);
		tstring = tstring->next;
	}
	return (full_len);
}

void	cat_tstring(t_token *current, char *assembled, int	*i)
{
	int			j;
	t_string	*current_tstring;

	current_tstring = current->tstring;
	while (current_tstring != NULL)
	{
		j = 0;
		while (current->tstring->str[j] != '\0')
		{
			assembled[*i] = current->tstring->str[j];
			(*i)++;
			j++;
		}
		current_tstring = current_tstring->next;
	}
	assembled[*i] = '\0';
}

int	assemble_tstring(t_token *tokens)
{
	int		i;
	char	*assembled;
	t_token	*current;

	current = tokens;
	while (tokens != NULL)
	{
		i = 0;
		assembled = malloc((get_full_len(current) + 1) * sizeof(char));
		if (assembled == NULL)
		{
			return (0); //ft_clean exit
		}
		cat_tstring(current, assembled, &i);
		current->assembled = assembled;
		current = current->next;
	}
}
