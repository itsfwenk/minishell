/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:23:53 by fli               #+#    #+#             */
/*   Updated: 2024/08/16 20:07:27 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	echo_newline(char **echo_arg)
{
	int	i;

	if (echo_arg[0][0] == '-')
	{
		i = 1;
		while (echo_arg[0][i] != '\0')
		{
				if (echo_arg[0][i] != 'n')
				{
					return (FALSE);
				}
				i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

int	ft_echo(char **echo_arg)
{
	int	i;
	int	newline;

	newline = echo_newline(echo_arg);
	if (newline == FALSE)
	{
		printf("%s", echo_arg[0]);
		if (echo_arg[1] != NULL)
		{
			printf(" ");
		}
	}
	i = 1;
	while (echo_arg[i] != NULL)
	{
		printf("%s", echo_arg[i]);
		if (echo_arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline == TRUE)
		printf("\n");
	return (0);
}

// int	main(int ac, char **av)
// {
// 	ft_echo(&av[1]);
// }
