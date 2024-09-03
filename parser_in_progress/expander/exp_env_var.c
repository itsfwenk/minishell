/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:31:32 by fli               #+#    #+#             */
/*   Updated: 2024/09/03 15:04:35 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exp_check_keys(t_string *current)
{
	int		i;

	i = 0;
	while (current->str[i] != '\0')
	{
		if (current->str[i] == '$')

	}
}

void	exp_in_brackets(t_string *current)
{
	int		i;

	i = 0;
	while (current->str[i] != '\0')
	{
		if (current->str[i] == '$')

	}
}
