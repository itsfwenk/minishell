/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:08:00 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/06 02:13:10 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

int	ft_pwd(char **args)
{
	char	pwd[PATH_MAX];
	int		i;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] != '-')
			continue ;
		if (ft_strcmp(args[i], "-L") && ft_strcmp(args[i], "-P")
			&& ft_strcmp(args[i], "-LP"))
		{
			ft_print_error("pwd", args[i],
				"invalid option\npwd: usage: pwd [-LP]", "\0");
			return (2);
		}
	}
	if (!(getcwd(pwd, sizeof(pwd))))
	{
		ft_print_error("pwd", NULL, "error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory", NULL);
		return (1);
	}
	printf("%s\n", pwd);
	return (0);
}
