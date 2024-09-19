/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:45:49 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/19 15:31:51 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key(char *key)
{
	size_t	i;

	i = 0;
	while (key[i])
	{
		if (!i && !ft_isalpha(key[i]) && key[i] != '_')
			return (0);
		if (i && !ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_builtin(char	*cmd)
{
	return (!ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "exit") ||
		!ft_strcmp(cmd, "export") ||
		!ft_strcmp(cmd, "pwd") ||
		!ft_strcmp(cmd, "unset"));
}
