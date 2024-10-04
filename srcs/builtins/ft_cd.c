/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:05:28 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 03:04:45 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static int	try_cd_home(t_env *env)
{
	t_env	*home;
	char	*go_home[2];

	home = get_env(env, "HOME");
	if (home && home->is_exported && !home->is_unset)
	{
		go_home[0] = home->value;
		go_home[1] = NULL;
		return (ft_cd(env, go_home));
	}
	ft_print_error("cd", NULL, "HOME not set", "\0");
	return (1);
}

int	ft_cd(t_env	*env, char **args)
{
	char	cwd[PATH_MAX];
	char	nwd[PATH_MAX];

	if (!args[0])
		return (try_cd_home(env));
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
