/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:41:07 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/18 19:00:38 by fli              ###   ########.fr       */
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

void	exec_parentheses(t_skibidi *skibidishell, t_token *tree)
{
	if (tree->type == PAR_STR)
	{
		tree->pid = ft_lstnew_pipex(tree);
		if (tree->pid == NULL || pipe(tree->pid->pipefd) == -1)
			ft_free_clean(skibidishell);
		tree->pid->p_id = fork();
		if (tree->pid->p_id == -1)
			ft_free_clean(skibidishell);
		if (tree->pid->p_id == 0)
			exec_tree(skibidishell, create_tree(tree->sub_shell), -1, -1);
	}
}

static int	get_fd(t_token	*redirection, t_skibidi *skibidishell, t_token *tree)
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

static int	dup_fd(int fd_redir, t_token *redirection, t_token *tree)
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
		fd_redir = get_fd(redirection, skibidishell, tree);
		if (fd_redir == -1)
			return (FALSE);
		if (dup_fd(fd_redir, redirection, tree) == FALSE)
			return (FALSE);
		close(fd_redir);
	}
	if (pipetab != NULL && side == LEFT)
	{
		if (dup2(pipetab[1], STDOUT_FILENO) == -1)
		{
			close_pipe(pipetab);
			return (FALSE);
		}
	}
	close_pipe(pipetab);
	return (TRUE);
}

static void	add_args(char **array, t_token *arguments, t_skibidi *skibidishell)
{
	int			i;
	t_string	*expanded_list;

	i = 1;
	while (arguments != NULL)
	{
		expanded_list = arguments->expanded_list;
		while (expanded_list != NULL)
		{
			array[i] = ft_strdup(expanded_list->str);
			if (array[i] == NULL)
			{
				free_all(array);
				ft_free_clean(skibidishell);
			}
			expanded_list = expanded_list->next;
			i++;
		}
		arguments = arguments->next;
	}
}

static void	create_argv(t_token *tokens, t_skibidi *skibidishell)
{
	char		**array;
	t_token		*arguments;

	array = ft_calloc(get_arg_nb(tokens) + 2, sizeof(char *));
	if (array == NULL)
		ft_free_clean(skibidishell);
	arguments = tokens->arguments;
	array[0] = ft_strdup(tokens->assembled);
	if (array[0] == NULL)
	{
		free_all(array);
		ft_free_clean(skibidishell);
	}
	add_args(array, arguments, skibidishell);
	tokens->argv = array;
}

static void	cmd_exec(t_skibidi *skibidishell, t_token *tree)
{
	char	**envp;
	char	*cmd_path;

	cmd_path = get_pathname(skibidishell, tree->assembled);
	if (cmd_path == NULL)
	{
		//printf bash: [cmd]: command not found
		ft_free_clean(skibidishell); // to modif to take exit code
		exit(127);
	}
	envp = build_envp(skibidishell->env);
	if (envp == NULL)
		ft_free_clean(skibidishell);
	create_argv(tree, skibidishell);
	if (execve(cmd_path, tree->argv, envp) == -1)
	{
		free(cmd_path);
		ft_free_clean(skibidishell);
		exit(EXIT_FAILURE);
	}
}

int	exec_cmd(t_skibidi *skibidishell, t_token *tree, int *pipetab, int side)
{
	if (tree->type == STR)
	{
		tree->pid = ft_lstnew_pipex(tree, skibidishell);
		tree->pid->p_id = fork();
		if (tree->pid->p_id == -1)
			ft_free_clean(skibidishell);
		if (tree->pid->p_id == 0)
		{
			fd_manager(tree, pipetab, side, skibidishell);
			cmd_exec(skibidishell, tree);
		}
		if (pipetab != NULL)
		{
			if (dup2(pipetab[0], STDIN_FILENO) == -1)
			{
				close_pipe(pipetab);
				return (FALSE);
			}
			close_pipe(pipetab);
			return (TRUE);
		}
	}
	return (TRUE);
}

int	exec_tree(t_skibidi *skibidishell, t_token *tree, int *pipetab, int side)
{
	int	exit_code;

	if (tree == NULL)
		return ;
	if (tree->type == PIPE)
	{
		if (pipe(tree->pid->pipefd) == -1)
			ft_free_clean(skibidishell);
		pipetab = tree->pid->pipefd;
	}
	exit_code = exec_tree(skibidishell, tree->left, pipetab, LEFT);
	if ((tree->type == AND && exit_code == TRUE) || tree->type == PIPE)
		exit_code = exec_tree(skibidishell, tree->right, pipetab, RIGHT);
	exec_parentheses(skibidishell, tree);
	exec_cmd(skibidishell, tree, pipetab, side);
}
