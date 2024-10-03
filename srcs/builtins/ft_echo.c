/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:05:47 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/03 23:59:05 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static bool	only_n(char **args, int arg_i)
{
	int	i;

	i = 1;
	while (args[arg_i][i] != '\0')
	{
		if (args[arg_i][i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(char **args)
{
	int	arg_i;
	int	newline;

	arg_i = 0;
	newline = true;
	if (args[arg_i] != NULL && args[arg_i][0] == '-')
	{
		if (only_n(args, arg_i) == true)
			newline = false;
	}
	while (args[arg_i] != NULL && args[arg_i][0] == '-'
			&& only_n(args, arg_i) == true)
	{
		arg_i++;
	}
	while (args[arg_i] != NULL)
	{
		printf("%s", args[arg_i]);
		if (args[arg_i + 1] != NULL)
			printf(" ");
		arg_i++;
	}
	if (newline == true)
		printf("\n");
	return (0);
}
