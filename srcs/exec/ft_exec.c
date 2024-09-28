/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:45:11 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 22:33:23 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

int	get_arg_nb(t_token *tokens)
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

void	add_every_wc(t_skibidi *shell, char **array,
	t_token *token, int *i)
{
	t_string	*cmd;

	cmd = token->wildcard_list;
	while (cmd != NULL)
	{
		array[*i] = ft_strdup(cmd->str);
		if (array[*i] == NULL)
		{
			free_str_tab(array);
			exit_shell(shell);
		}
		cmd = cmd->next;
		*i = *i + 1;
	}
}

void	add_args(t_skibidi *shell, char **array,
	t_token *arguments, int *i)
{
	t_token	*arg_token;

	arg_token = arguments;
	while (arg_token != NULL)
	{
		add_every_wc(shell, array, arg_token, i);
		arg_token = arg_token->next;
	}
}

static bool	special_exec(t_skibidi *shell, t_token *tree, int *pipetab)
{
	if (tree->type == AND)
	{
		waitpid(tree->left->pid->p_id, &tree->left->pid->status, 0);
		if (WEXITSTATUS(tree->left->pid->status) == EXIT_FAILURE)
			return (false);
	}
	if (tree->type == OR)
	{
		waitpid(tree->left->pid->p_id, &tree->left->pid->status, 0);
		if (WEXITSTATUS(tree->left->pid->status) == EXIT_SUCCESS)
			return (false);
	}
	exec_tree(shell, tree->right, pipetab, RIGHT);
	return (true);
}

bool	exec_tree(t_skibidi *shell, t_token *tree, int *pipetab, t_side side)
{
	if (tree == NULL)
		return (false);
	tree->pid = ft_lstnew_pipex(shell);
	if (tree->type == PIPE)
	{
		if (tree->left->previous_pipe == NULL)
			tree->right->previous_pipe = pipetab;
		if (pipe(tree->pid->pipefd) == -1)
			exit_shell(shell);
		pipetab = tree->pid->pipefd;
	}
	exec_tree(shell, tree->left, pipetab, LEFT);
	if ((tree->type == PIPE || tree->type == AND || tree->type == OR)
		&& !special_exec(shell, tree, pipetab))
		return (false);
	exec_parentheses(shell, tree, pipetab, side);
	exec_cmd(shell, tree, pipetab, side);
	if (tree->type == PIPE)
		close_pipe(tree->pid->pipefd);
	return (true);
}
