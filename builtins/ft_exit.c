/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:12:55 by fli               #+#    #+#             */
/*   Updated: 2024/08/19 17:12:22 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static unsigned long long	ex_atoull(const char *nptr)
{
	int					i;
	unsigned long long	nbr;

	if (ft_strlen(nptr) >= 20)
		return (9223372036854775809ULL);
	i = 0;
	nbr = 0;
	while (nptr [i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10;
		nbr = nbr + (nptr[i++] - '0');
	}
	if (nbr > 9223372036854775808ULL)
		return (9223372036854775809ULL);
	return (nbr);
}

static void	init_ex_isnumeric(const char *nptr, int *i, int *sign, int *start)
{
	*sign = 1;
	*start = 0;
	if (nptr[*start] == '-')
	{
		*start = 1;
		*sign = -1;
	}
	*i = *start;
}

static int	ex_isnumeric(const char *nptr)
{
	int	i;
	int	sign;
	int	start;

	init_ex_isnumeric(nptr, &i, &sign, &start);
	while (nptr[i] != '\0')
	{
		if (ft_isdigit(nptr[i]) == 0)
			return (FALSE);
		i++;
	}
	if (ex_atoull(&nptr[start]) == 9223372036854775809ULL)
		return (FALSE);
	if (ex_atoull(&nptr[start]) == 9223372036854775808ULL)
	{
		if (sign == -1)
			return (TRUE);
		else
			return (FALSE);
	}
	return (TRUE);
}

static void	one_valid_arg(char **exit_arg)
{
	printf("exit\n");
	if (exit_arg[0][0] == '-')
		exit(ex_atoull(++exit_arg[0]) * -1);
	else
		exit(ex_atoull(exit_arg[0]));
}

int	ft_exit(char **ex_arg)
{
	if (ex_arg[0] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (ex_isnumeric(ex_arg[0]) == TRUE)
	{
		if (ex_arg[1] == NULL)
			one_valid_arg(ex_arg);
		else
		{
			ft_dprintf(2, "exit\nminishell: exit: too many arguments");
			return (1);
		}
	}
	else
	{
		write(2, "exit\nminishell: exit: ", 22);
		ft_dprintf(2, "%s: numeric argument required", ex_arg[0]);
		exit(2);
	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	ft_exit(&av[1]);
// }
