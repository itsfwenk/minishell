/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:41:07 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/24 13:22:35 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec_tree(t_token *tree)
// {
// 	if (!tree)
// 		return ;
// 	exec_tree(tree->left);
// 	ft_dprintf(2, "%s %s %s\n", tree->left->full_string, tree->full_string, tree->right->full_string);
// 	exec_tree(tree->right);
// }

// int	ft_exec(t_skibidi *skibidishell)
// {
// 	t_token	*tree;

// 	tree = skibidishell->tree;
// }

void	exec_parentheses(t_skibidi *skibidishell, t_token *tree, int *pipetab, int side)
{
	if (tree->type == PAR_STR)
	{
		tree->pid = ft_lstnew_pipex(skibidishell);
		if (tree->pid == NULL)
			ft_free_clean(skibidishell);
		tree->pid->p_id = fork();
		if (tree->pid->p_id == -1)
			ft_free_clean(skibidishell);
		if (tree->pid->p_id == 0)
			exec_tree(skibidishell, create_tree(tree->sub_shell), pipetab, side);
	}
}

static int	get_fd(t_token	*redirection, t_skibidi *skibidishell)
{
	int		fd_redir;

	fd_redir = -1;
	if (redirection->type == IN_REDIR)
		fd_redir = open(redirection->next->assembled, O_RDONLY);
	if (redirection->type == HERE_DOC)
		fd_redir = get_here_doc_content(redirection, skibidishell);
	if (redirection->type == OUT_REDIR)
		fd_redir = open(redirection->next->assembled, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirection->type == APD_OUT_REDIR)
		fd_redir = open(redirection->next->assembled, O_WRONLY | O_CREAT | O_APPEND, 0644);
	redirection->fd = fd_redir;
	// if (fd_redir == -1)
		// close_all_fd(tree);
	// error message
	return (fd_redir);
}

static int	dup_fd(int fd_redir, t_token *redirection)
{
	int		dup_return;

	if (redirection->type == IN_REDIR || redirection->type == HERE_DOC)
		dup_return = dup2(fd_redir, STDIN_FILENO);
	if (redirection->type == OUT_REDIR || redirection->type == APD_OUT_REDIR)
		dup_return = dup2(fd_redir, STDOUT_FILENO);
	if (dup_return == -1)
	{
		close(fd_redir);
		return (FALSE);
	}
	return (TRUE);
}

void	close_pipe(int pipefd[2])
{
	if (pipefd == NULL)
		return ;
	close(pipefd[0]);
	close(pipefd[1]);
}

int	fd_manager(t_token *tree, int *pipetab, int side, t_skibidi *skibidishell)
{
	int		fd_redir;
	t_token	*redirection;

	fd_redir = -1;
	redirection = tree->redir;
	while (redirection != NULL)
	{
		fd_redir = get_fd(redirection, skibidishell);
		if (fd_redir == -1)
			return (FALSE);
		if (dup_fd(fd_redir, redirection) == FALSE)
			return (FALSE);
		close(fd_redir);
		redirection = redirection->next->next;
	}
	if (pipetab != NULL && side == LEFT)
	{
		if (dup2(pipetab[1], STDOUT_FILENO) == -1)
		{
			close_pipe(pipetab);
			return (FALSE);
		}
		close_pipe(pipetab);
	}
	if (pipetab != NULL && side == RIGHT)
	{
		if (dup2(pipetab[0], STDIN_FILENO) == -1)
		{
			close_pipe(pipetab);
			return (FALSE);
		}
		close_pipe(pipetab);
	}
	if (tree->previous_pipe != NULL && side == RIGHT)
	{
		if (dup2(tree->previous_pipe[1], STDOUT_FILENO) == -1)
		{
			close_pipe(tree->previous_pipe);
			return (FALSE);
		}
		close_pipe(tree->previous_pipe);
		return (TRUE);
	}
	return (TRUE);
}

static int	get_arg_nb(t_token *tokens)
{
	int			i;
	t_string	*token_wildcarded;
	t_token		*arguments;

	i = 0;
	token_wildcarded = tokens->wildcard_list;
	while (token_wildcarded)
	{
		i++;
		token_wildcarded = token_wildcarded->next;
	}
	arguments = tokens->arguments;
	while (arguments != NULL)
	{
		token_wildcarded = arguments->wildcard_list;
		while (token_wildcarded)
		{
			i++;
			token_wildcarded = token_wildcarded->next;
		}
		i++;
		arguments = arguments->next;
	}
	return (i);
}

static void	add_every_wc(char **array, t_token *token, t_skibidi *skibidishell, int *i)
{
	t_string	*cmd;

	cmd = token->wildcard_list;
	while (cmd != NULL)
	{
		array[*i] = ft_strdup(cmd->str);
		if (array[*i] == NULL)
		{
			free_all(array);
			ft_free_clean(skibidishell);
		}
		cmd = cmd->next;
		*i = *i + 1;
	}
}

static void	add_args(char **array, t_token *arguments, t_skibidi *skibidishell, int *i)
{
	t_token	*arg_token;

	arg_token = arguments;
	while (arg_token != NULL)
	{
		add_every_wc(array, arg_token, skibidishell, i);
		arg_token = arg_token->next;
	}
}

static void	create_argv(t_token *tokens, t_skibidi *skibidishell)
{
	int			i;
	char		**array;
	t_token		*arguments;

	array = ft_calloc(get_arg_nb(tokens) + 1, sizeof(char *));
	if (array == NULL)
		ft_free_clean(skibidishell);
	arguments = tokens->arguments;
	i = 0;
	add_every_wc(array, tokens, skibidishell, &i);
	add_args(array, arguments, skibidishell, &i);
	tokens->argv = array;
}

static int	builtin_exec(t_skibidi	*skibidishell, char	*cmd, char	**argv)
{
	int	exit_code;

	exit_code = 0;
	if (!ft_strcmp(cmd, "cd"))
		exit_code = ft_cd(skibidishell->env, &argv[1]);
	else if (!ft_strcmp(cmd, "echo"))
		exit_code = ft_echo(&argv[1]);
	else if (!ft_strcmp(cmd, "env"))
		exit_code = ft_env(skibidishell->env);
	else if (!ft_strcmp(cmd, "exit"))
		exit_code = ft_exit(&argv[1]);
	else if (!ft_strcmp(cmd, "export"))
		exit_code = ft_export(skibidishell, &argv[1]);
	else if (!ft_strcmp(cmd, "pwd"))
		exit_code = ft_pwd();
	else if (!ft_strcmp(cmd, "unset"))
		exit_code = ft_unset(skibidishell->env, &argv[1]);
	return (exit_code);
}

static void	cmd_exec(t_skibidi *skibidishell, t_token *tree)
{
	char	**envp;
	char	*cmd_path;
	int		builtin;

	builtin = is_builtin(tree->assembled);
	if (builtin)
		cmd_path = tree->assembled;
	else
		cmd_path = get_pathname(skibidishell, tree->assembled);
	if (builtin)
		exit(builtin_exec(skibidishell, cmd_path, tree->argv));
	else
	{
		if (cmd_path == NULL)
		{
			ft_free_clean(skibidishell); // to modif to take exit code
			exit(127);
		}
		envp = build_envp(skibidishell->env);
		if (envp == NULL)
			ft_free_clean(skibidishell);
		if (execve(cmd_path, tree->argv, envp) == -1)
		{
			free(cmd_path);
			ft_free_clean(skibidishell);
			exit(EXIT_FAILURE);
		}
	}
}

int	only_builtins(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == PAR_STR && !only_builtins(tokens->sub_shell))
			return (0);
		else if (tokens->type == STR && !is_builtin(tokens->assembled))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

static int	exec_cmd(t_skibidi *skibidishell, t_token *tree, int *pipetab, int side)
{
	if (tree->type == STR)
	{
		ft_expander(skibidishell, tree);
		assemble_tstring(skibidishell, tree);
		get_filenames(tree, skibidishell);
		create_argv(tree, skibidishell);
		if (skibidishell->tokens->next == NULL && only_builtins(skibidishell->tokens))
			builtin_exec(skibidishell, tree->assembled, tree->argv);
		else
		{
			tree->pid->p_id = fork();
			if (tree->pid->p_id == -1)
				ft_free_clean(skibidishell);
			if (tree->pid->p_id == 0)
			{
				if (fd_manager(tree, pipetab, side, skibidishell) == FALSE)
				{
					dprintf(2, "fd failed\n");
					ft_free_clean(skibidishell);
				}
				cmd_exec(skibidishell, tree);
			}
		}
	}
	return (TRUE);
}

int	exec_tree(t_skibidi *skibidishell, t_token *tree, int *pipetab, int side)
{
	if (tree == NULL)
		return (FALSE);
	tree->pid = ft_lstnew_pipex(skibidishell);
	if (tree->type == PIPE)
	{
		tree->right->previous_pipe = pipetab;
		if (pipe(tree->pid->pipefd) == -1)
			ft_free_clean(skibidishell);
		pipetab = tree->pid->pipefd;
	}
	exec_tree(skibidishell, tree->left, pipetab, LEFT);
	if (tree->type == PIPE || tree->type == AND || tree->type == OR)
	{
		if (tree->type == AND)
		{
			waitpid(tree->left->pid->p_id, &tree->left->pid->status, 0);
			if (WEXITSTATUS(tree->left->pid->status) == EXIT_FAILURE)
				return (FALSE);
		}
		if (tree->type == OR)
		{
			waitpid(tree->left->pid->p_id, &tree->left->pid->status, 0);
			if (WEXITSTATUS(tree->left->pid->status) == EXIT_SUCCESS)
				return (FALSE);
		}
		exec_tree(skibidishell, tree->right, pipetab, RIGHT);
	}
	exec_parentheses(skibidishell, tree, pipetab, side);
	exec_cmd(skibidishell, tree, pipetab, side);
	if (tree->type == PIPE)
		close_pipe(tree->pid->pipefd);
	return (TRUE);
}
