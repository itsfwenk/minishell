/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:05:28 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/06 01:28:03 by mel-habi         ###   ########.fr       */
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
	char	nwd[PATH_MAX];
	t_env	*pwd;

	if (!args[0] || (!ft_strcmp(args[0], "~") && !args[1]))
		return (try_cd_home(env));
	else if (args[1])
	{
		ft_print_error("cd", NULL, "too many arguments", "\0");
		return (1);
	}
	else if (!args[0][0])
		return (0);
	if (chdir(args[0])
		|| !getcwd(nwd, sizeof(nwd)))
	{
		ft_print_error("cd", args[0], strerror(errno), "\0");
		return (1);
	}
	pwd = get_env(env, "PWD");
	if (pwd && pwd->is_exported && !pwd->is_unset)
		add_env(&env, "OLDPWD", pwd->value);
	else
		return (unset_env(env, "OLDPWD"), unset_env(env, "PWD"), 0);
	add_env(&env, "PWD", nwd);
	return (0);
}
