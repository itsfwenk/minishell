/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:21:27 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/30 20:30:31 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static int	builtin_exec(t_skibidi	*shell, char	*cmd, char	**argv,
	bool in_child)
{
	int	exit_code;

	exit_code = 0;
	if (!ft_strcmp(cmd, "cd"))
		exit_code = ft_cd(shell->env, &argv[1]);
	else if (!ft_strcmp(cmd, "echo"))
		exit_code = ft_echo(&argv[1]);
	else if (!ft_strcmp(cmd, "env"))
		exit_code = ft_env(shell->env);
	else if (!ft_strcmp(cmd, "exit"))
		exit_code = ft_exit(&argv[1]);
	else if (!ft_strcmp(cmd, "export"))
		exit_code = ft_export(shell, &argv[1]);
	else if (!ft_strcmp(cmd, "pwd"))
		exit_code = ft_pwd();
	else if (!ft_strcmp(cmd, "unset"))
		exit_code = ft_unset(shell->env, &argv[1]);
	shell->exit_code = exit_code;
	update_error_code(shell, exit_code, true);
	if (!in_child)
		return (exit_code);
	lx_deltokens(&shell->tokens);
	free_env(shell->env);
	free(shell);
	return (exit_code);
}

static void	create_argv(t_skibidi *shell, t_token *tokens)
{
	int			i;
	char		**array;
	t_token		*arguments;

	array = ft_calloc(get_arg_nb(tokens) + 1, sizeof(char *));
	if (array == NULL)
		exit_shell(shell);
	arguments = tokens->arguments;
	i = 0;
	add_every_wc(shell, array, tokens, &i);
	add_args(shell, array, arguments, &i);
	tokens->argv = array;
}

static void	cmd_exec(t_skibidi *shell, t_token *tree)
{
	char	**envp;
	char	*cmd_path;
	int		builtin;

	builtin = is_builtin(tree->assembled);
	if (builtin)
		cmd_path = tree->assembled;
	else
		cmd_path = get_pathname(shell, tree->assembled);
	if (builtin)
		exit(builtin_exec(shell, cmd_path, tree->argv, true));
	if (cmd_path == NULL)
		exit_shell(shell);
	envp = build_envp(shell->env);
	if (envp == NULL)
		exit_shell(shell);
	if (execve(cmd_path, tree->argv, envp) == -1)
	{
		free_str_tab(envp);
		free(cmd_path);
		exit_shell(shell);
		exit(EXIT_FAILURE);
	}
}

int	exec_cmd(t_skibidi *shell, t_token *tree, int *pipetab, t_side side)
{
	if (ft_expander(shell, tree) == false)
		return (false);
	assemble_tstring(shell, tree);
	check_for_heredoc(shell, tree);
	get_filenames(shell, tree);
	create_argv(shell, tree);
	add_env(&shell->env, "_", tree->assembled);
	if (g_signal)
		return (true);
	else if (is_builtin(tree->assembled))
		return (!builtin_exec(shell, tree->assembled, tree->argv, false));
	tree->pid->p_id = fork();
	if (tree->pid->p_id == -1)
		exit_shell(shell);
	if (tree->pid->p_id == 0)
	{
		if (fd_manager(shell, tree, pipetab, side) == false)
			exit_shell(shell);
		close_pipe(pipetab);
		close_pipe(tree->previous_pipe);
		cmd_exec(shell, tree);
	}
	return (true);
}
