/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:50:41 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/17 17:31:44 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static char	*free_and_trim(char *str)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = str;
	str = ft_strtrim(str, " \t\n\v\f\r");
	free(tmp);
	return (str);
}

// static void	print_token(int token_type)
// {
// 	if (token_type == PIPE)
// 		dprintf(2, "PIPE");
// 	if (token_type == OR)
// 		dprintf(2, "OR");
// 	if (token_type == APD_OUT_REDIR)
// 		dprintf(2, "APD_OUT_REDIR");
// 	if (token_type == OUT_REDIR)
// 		dprintf(2, "OUT_REDIR");
// 	if (token_type == HERE_DOC)
// 		dprintf(2, "HERE_DOC");
// 	if (token_type == IN_REDIR)
// 		dprintf(2, "IN_REDIR");
// 	if (token_type == AND)
// 		dprintf(2, "AND");
// 	if (token_type == STR)
// 		dprintf(2, "STR");
// 	if (token_type == HD_LIMITER)
// 		dprintf(2, "HD_LIMITER");
// 	if (token_type == FILENAME)
// 		dprintf(2, "FILENAME");
// 	if (token_type == PAR_STR)
// 		dprintf(2, "PAR_STR");
// }

// static void print_tree(t_token *tree)
// {
// 	if (!tree)
// 		return ;
// 	print_tree(tree->left);
// 	print_token(tree->type);
// 	dprintf(2, " %s\n", tree->full_string);
// 	if (tree->arguments)
// 	{
// 		dprintf(2, "ARGS: ");
// 		while (tree->arguments)
// 		{
// 			dprintf(2, "%s, ", tree->arguments->full_string);
// 			tree->arguments = tree->arguments->next;
// 		}
// 		dprintf(2, "\n");
// 	}
// 	print_tree(tree->right);
// }

static int 	only_redirs(t_token *token)
{
	while (token)
	{
		if (token->type == STR || token->type == PAR_STR)
			return (FALSE);
		token = token->next;
	}
	return (TRUE);
}

// void	exec_tree(t_token *tree)
// {
// 	if (!tree || !tree->left || !tree->right)
// 		return ;
// 	exec_tree(tree->left);
// 	if (tree->left->type == PAR_STR)
// 		exec_tree(create_tree(tree->left));
// 	else
// 		ft_dprintf(2, "%s ", tree->left->full_string);
// 	ft_dprintf(2, "%s ", tree->full_string);
// 	if (tree->right->type == PAR_STR)
// 		exec_tree(create_tree(tree->right));
// 	else
// 		ft_dprintf(2, "%s ", tree->right->full_string);
// 	ft_dprintf(2, "\n");
// 	exec_tree(tree->right);
// }

int	exec_tree(t_token *tree)
{
	int	exit_code;

	if (tree == NULL)
		return ;
	exit_code = exec_tree(tree->left);
	if ((tree->type == AND && exit_code == TRUE) || tree->type == PIPE)
		exit_code = exec_tree(tree->right);
	if (tree->type == PAR_STR)
	{

	}
}

static void	handle_line(char *line, t_skibidi *skibidishell)
{
	skibidishell->tokens = ft_lexer(line, skibidishell);
	check_syntax(skibidishell->tokens);
	assemble_tstring(skibidishell);
	if (!only_redirs(skibidishell->tokens))
	{
		merge_tokens(skibidishell, &(skibidishell->tokens), NULL);
		skibidishell->tree = create_tree(skibidishell->tokens);
		exec_tree(skibidishell->tree);
	}
	//exec
}

static int	check_line(char *line)
{
	int	well_formated;

	well_formated = is_well_formated(line);
	if (well_formated == -1)
	{
		ft_print_error(NULL, ")", \
				"syntax error near unexpected token", "`'");
		return (2);
	}
	else if (finished_by_meta(line) || !is_brace_well_formated(line)
		|| has_semicolon(line) || !well_formated)
	{
		ft_print_error("check_line", NULL, \
				"unexpected line", NULL);
		return (2);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_skibidi	*skibidishell;
	char		*line;

	(void)argv;
	(void)argc;
	skibidishell = ft_calloc(1, sizeof(t_skibidi));
	if (!skibidishell)
		return (2);
	if (!ft_export(skibidishell, envp) && reset_utils_env(&skibidishell->env))
	{
		line = ft_strdup("apd cmd1 arg1 | cmd2 arg2 << heredoc2");
		while (line)
		{
			if (line[0])
			{
				g_signal = check_line(line);
				if (g_signal != 2)
				{
					add_history(line);
					handle_line(line, skibidishell);
				}
			}
			free(line);
			reset_utils_env(&skibidishell->env);
			line = free_and_trim(readline(ft_get_prompt(g_signal)));
		}
	}
	rl_clear_history();
	ft_free_clean(skibidishell);
	return (0);
}
