/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_pos_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:13:33 by fli               #+#    #+#             */
/*   Updated: 2024/09/06 11:08:33 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exp_dup_pos_param(t_string *current, char *expanded_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (current->str[i] != '\0')
	{
		if (current->str[i] == '$'
			&& current->str[i + 1] != '\0'
			&& ft_isdigit(current->str[i + 1]) != FALSE)
		{
			i = i + 2;
			continue;
		}
		expanded_str[j] = current->str[i];
		j++;
		i++;
	}
	expanded_str[j] = '\0';
	free(current->str);
	current->str = expanded_str;
}

void	exp_pos_param(t_string *current)
{
	int		i;
	int		nb_pos_param;
	char	*expanded_str;

	i = 0;
	nb_pos_param = 0;
	while (current->str[i] != '\0')
	{
		if (current->str[i] == '$' && (ft_isdigit(current->str[i + 1]) != FALSE
				|| current->str[i + 1] == '*' || current->str[i + 1] == '@'))
		{
			nb_pos_param++;
			i = i + 2;
			continue;
		}
		i++;
	}
	if (nb_pos_param == 0)
		return ;
	expanded_str = malloc(1 + (ft_strlen(current->str) - (2 * nb_pos_param)));
	if (expanded_str == NULL)
	{
		return ; // ft_exit
	}
	exp_dup_pos_param(current, expanded_str);
}
