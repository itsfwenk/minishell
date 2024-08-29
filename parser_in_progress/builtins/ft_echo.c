/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:23:53 by fli               #+#    #+#             */
/*   Updated: 2024/08/23 12:07:29 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_n(char **echo_arg, int arg_i)
{
	int	i;

	i = 1;
	while (echo_arg[arg_i][i] != '\0')
	{
		if (echo_arg[arg_i][i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_echo(char **echo_arg)
{
	int	arg_i;
	int	newline;

	arg_i = 0;
	newline = TRUE;
	if (echo_arg[arg_i] != NULL && echo_arg[arg_i][0] == '-')
	{
		if (only_n(echo_arg, arg_i) == TRUE)
			newline = FALSE;
	}
	while (echo_arg[arg_i] != NULL && echo_arg[arg_i][0] == '-'
			&& only_n(echo_arg, arg_i) == TRUE)
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
	if (newline == TRUE)
		printf("\n");
	return (0);
}
