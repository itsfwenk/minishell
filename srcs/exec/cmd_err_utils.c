/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_err_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:27:54 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 16:01:14 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

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
	if (S_ISDIR(path_stat.st_mode))
		ft_print_error(tree->argv[0], NULL, "Is a directory", NULL);
	else
		ft_print_error(tree->argv[0], NULL, "Permission denied", NULL);
	free(cmd_path);
	exit_shell(shell);
}
