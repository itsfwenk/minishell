/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:31:17 by fli               #+#    #+#             */
/*   Updated: 2024/08/23 11:40:47 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	update_dvarenv(t_env *varenv, char *old, char *new)
// {
// 	t_env	*new_pwd;
// 	t_env	*old_pwd;

// 	new_pwd = varenv;
// 	while (ft_strncmp(new_pwd->key, "PWD", ft_strlen("PWD")) != 0)
// 	{
// 		new_pwd = new_pwd->next;
// 	}
// 	if (new_pwd != NULL)
// 		ft_strlcpy(new_pwd->value, new, PATH_MAX);
// 	old_pwd = varenv;
// 	while (ft_strncmp(new_pwd->key, "OLDPWD", ft_strlen("OLDPWD")) != 0)
// 	{
// 		old_pwd = old_pwd->next;
// 	}
// 	if (new_pwd == NULL)
// 	{
// 		unset_env(varenv, "PWD");
// 		unset_env(varenv, "OLDPWD");
// 	}
// 	if (old_pwd != NULL)
// 		ft_strlcpy(old_pwd->value, old, PATH_MAX);
// }

int	ft_cd(char **dir_path)
{
	char	cwd[PATH_MAX];
	char	nwd[PATH_MAX];

	if (dir_path[1])
		return (ft_print_error("cd", NULL, "too many arguments", NULL), 1);
	else if (dir_path == NULL)
		return (0);
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
	return (errno);
}
