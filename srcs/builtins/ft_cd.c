/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:05:28 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 00:03:07 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

int	ft_cd(t_env	*env, char **args)
{
	char	cwd[PATH_MAX];
	char	nwd[PATH_MAX];

	if (!args[0])
		return (0);
	else if (args[1])
	{
		ft_print_error("cd", NULL, "too many arguments", "\0");
		return (1);
	}
	if (!getcwd(cwd, sizeof(cwd))
		|| chdir(args[0])
		|| !getcwd(nwd, sizeof(nwd)))
	{
		ft_print_error("cd", args[0], strerror(errno), "\0");
		return (1);
	}
	add_env(&env, "OLDPWD", cwd);
	add_env(&env, "PWD", nwd);
	return (0);
}
