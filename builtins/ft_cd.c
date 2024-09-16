/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:31:17 by fli               #+#    #+#             */
/*   Updated: 2024/09/16 17:41:21 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **dir_path)
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
	return (errno);
}
