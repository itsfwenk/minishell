/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:05:47 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 19:10:09 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static bool	only_n(char **echo_arg, int arg_i)
{
	int	i;

	i = 1;
	while (echo_arg[arg_i][i] != '\0')
	{
		if (echo_arg[arg_i][i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(char **echo_arg)
{
	int	arg_i;
	int	newline;

	arg_i = 0;
	newline = true;
	if (echo_arg[arg_i] != NULL && echo_arg[arg_i][0] == '-')
	{
		if (only_n(echo_arg, arg_i) == true)
			newline = false;
	}
	while (echo_arg[arg_i] != NULL && echo_arg[arg_i][0] == '-'
			&& only_n(echo_arg, arg_i) == true)
	{
		arg_i++;
	}
	while (echo_arg[arg_i] != NULL)
	{
		printf("%s", echo_arg[arg_i]);
		if (echo_arg[arg_i + 1] != NULL)
			printf(" ");
		arg_i++;
	}
	if (newline == true)
		printf("\n");
	return (true);
}
