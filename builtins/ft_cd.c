/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:31:17 by fli               #+#    #+#             */
/*   Updated: 2024/08/18 17:43:05 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_dvarenv(t_env *varenv, char *old, char *new)
{
	t_env	*new_pwd;
	t_env	*old_pwd;

	new_pwd = varenv;
	while (ft_strncmp(new_pwd->key, "PWD", ft_strlen("PWD")) != 0)
	{
		new_pwd = new_pwd->next;
	}
	if (new_pwd != NULL)
		ft_strlcpy(new_pwd->value, new, PATH_MAX);
	old_pwd = varenv;
	while (ft_strncmp(new_pwd->key, "OLDPWD", ft_strlen("OLDPWD")) != 0)
	{
		old_pwd = old_pwd->next;
	}
	if (new_pwd == NULL)
	{
		// delete PWD and OLDPWD nods
	}
	if (old_pwd != NULL)
		ft_strlcpy(old_pwd->value, old, PATH_MAX);
}


int	ft_cd(char *dir_path)
{
	char cwd[PATH_MAX];
	char nwd[PATH_MAX];

	if (dir_path == NULL)
		return (0);
	getcwd(cwd, sizeof(cwd));
	if (cwd == NULL)
	{
		perror("getcwd() error");
		return (errno);
	}
	if (chdir(dir_path) != 0)
	{
		ft_dprintf(2, "bash: cd: %s: ", dir_path);
		perror("");
	}
	getcwd(nwd, sizeof(nwd));
	if (nwd == NULL)
	{
		perror("getcwd() error");
		return (errno);
	}
	return(errno);
}

// int	main(int ac, char **av)
// {
// 	char *cwd;


// 	cwd = getcwd(NULL, 0);
// 	if (cwd != NULL)
// 	{
// 		printf("Current working directory: %s\n", cwd);
// 		free(cwd);
// 	}

// 	ft_cd(av[1]);

// 	cwd = getcwd(NULL, 0);
// 	if (cwd != NULL)
// 	{
// 		printf("Changed working directory: %s\n", cwd);
// 		free(cwd);
// 	}
// }
