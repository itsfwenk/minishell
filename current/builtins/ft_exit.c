/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:12:55 by fli               #+#    #+#             */
/*   Updated: 2024/08/20 19:20:27 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned long long	ex_atoull(const char *nptr)
{
	int					i;
	unsigned long long	nbr;

	if (nptr[0] == '\0')
		return (0);
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
	while (nptr[*start] == '0')
	{
		(*start)++;
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
			ft_dprintf(2, "%sexit\n%s", RED, END_COLOR);
			ft_print_error("exit", NULL, "too many arguments", "\0");
			return (1);
		}
	}
	else
	{
		ft_dprintf(2, "%sexit\n%s", RED, END_COLOR);
		ft_print_error("exit", ex_arg[0], "numeric argument required", "\0");
		exit(2);
	}
	return (0);
}