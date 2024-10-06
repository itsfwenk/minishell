/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_err_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:27:54 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/06 01:13:18 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	special_cmd_path(t_skibidi *shell, t_token *tree, char *cmd_path)
{
	if (!ft_strcmp(tree->argv[0], "."))
	{
		shell->exit_code = 2;
		ft_print_error(".", NULL,
			"filename argument required\n.: \
usage: . filename [arguments]", "\0");
		if (cmd_path)
			free(cmd_path);
		exit_shell(shell);
	}
	cmd_not_found(shell, tree, cmd_path);
}

void	cmd_not_found(t_skibidi *shell, t_token *tree, char *cmd_path)
{
	(void)cmd_path;
	shell->exit_code = 127;
	ft_print_error(tree->argv[0], NULL, "command not found", NULL);
	if (cmd_path)
		free(cmd_path);
	exit_shell(shell);
}

void	cmd_no_perm(t_skibidi *shell, t_token *tree, char *cmd_path)
{
	struct stat	path_stat;

	shell->exit_code = 126;
	stat(cmd_path, &path_stat);
	if (!ft_strcmp(tree->argv[0], ".") || !ft_strcmp(tree->argv[0], ".."))
		special_cmd_path(shell, tree, cmd_path);
	else if (S_ISDIR(path_stat.st_mode))
		ft_print_error(tree->argv[0], NULL, "Is a directory", NULL);
	else if (S_ISREG(path_stat.st_mode))
		ft_print_error(tree->argv[0], NULL, "Permission denied", NULL);
	else
	{
		shell->exit_code = 127;
		ft_print_error(tree->argv[0], NULL, "No such file or directory", NULL);
	}
	free(cmd_path);
	exit_shell(shell);
}
