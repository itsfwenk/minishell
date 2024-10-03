/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:06:39 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 00:37:28 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static bool	is_nan(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (true);
		i++;
	}
	return (false);
}

static bool	check_overflow(int sign, unsigned long long r)
{
	if ((sign == 1 && r > (unsigned long long)LONG_MAX)
		|| (sign == -1 && r > (unsigned long long)LONG_MAX + 1))
		return (true);
	return (false);
}

static bool	has_overflow(char *str)
{
	size_t				i;
	int					s;
	unsigned long long	r;

	i = 0;
	s = 1;
	r = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (i && (str[i - 1] == '+' || str[i - 1] == '-'))
			return (0);
		else if (str[i] == '-')
			s *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		r = r * 10 + str[i] - 48;
		if (check_overflow(s, r))
			return (true);
		i++;
	}
	return (false);
}

int	ft_exit(t_skibidi *shell, char **args)
{
	int	exit_code;

	exit_code = 1;
	if (!shell->in_par)
		printf("exit\n");
	if (!args[0])
		exit_shell(shell);
	else if (!is_nan(args[0]) && !has_overflow(args[0]))
	{
		if (args[1])
			ft_print_error("exit", NULL, "too many arguments", "\0");
		else
		{
			exit_code = ft_atoi(args[0]);
			shell->to_exit = true;
		}
	}
	else
	{
		ft_print_error("exit", args[0], "numeric argument required", "\0");
		exit_code = 2;
	}
	return (exit_code);
}
