/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:05:28 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/30 19:45:58 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

int	ft_cd(t_env	*env, char **dir_path)
{
	char	cwd[PATH_MAX];
	char	nwd[PATH_MAX];

	if (!dir_path[0])
		return (0);
	else if (dir_path[1])
		return (ft_print_error("cd", NULL, "too many arguments", NULL), 1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return (errno);
	}
	if (chdir(dir_path[0]) != 0)
	{
		ft_dprintf(2, "bash: cd: %s: ", dir_path[0]);
		perror("");
	}
	if (getcwd(nwd, sizeof(nwd)) == NULL)
	{
		perror("getcwd() error");
		return (errno);
	}
	add_env(&env, "OLDPWD", cwd);
	add_env(&env, "PWD", nwd);
	return (errno);
}
