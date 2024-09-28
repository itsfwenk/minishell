/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:50:41 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 15:10:19 by fli              ###   ########.fr       */
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

static void	check_for_here_doc(t_skibidi *skibidishell)
{
	int		hd_return;
	t_token	*current;

	current = skibidishell->tokens;

	while (current)
	{
		if (current->type == HERE_DOC)
		{
			hd_return = get_here_doc_content(current, skibidishell);
			if (hd_return == -1)
				ft_free_clean(skibidishell);
		}
		current = current->next;
	}
}

static void	expd_wc_only_redir(t_skibidi *skibidishell)
{
	t_token	*token;

	token = skibidishell->tokens;
	while (token)
	{
		if (token->type != HD_LIMITER)
			ft_expander(skibidishell, token);
		assemble_tstring(skibidishell, token);
		get_filenames(token, skibidishell);
		token = token->next;
	}
}

static void	open_only_redir(t_skibidi *skibidishell)
{
	int		fd;
	t_token	*token;

	token = skibidishell->tokens;
	while (token)
	{
		fd = get_fd(token, skibidishell);
		close(fd);
		token = token->next;
	}
}

static void	handle_line(char *line, t_skibidi *skibidishell)
{
	skibidishell->tokens = ft_lexer(line, skibidishell);
	check_syntax(skibidishell->tokens);
	// assemble_tstring(skibidishell);
	if (!only_redirs(skibidishell->tokens))
	{
		merge_tokens(skibidishell, &(skibidishell->tokens), NULL);
		skibidishell->tree = create_tree(skibidishell->tokens);
		exec_tree(skibidishell, skibidishell->tree, NULL, -1);
	}
	else
	{
		expd_wc_only_redir(skibidishell);
		check_for_here_doc(skibidishell);
		open_only_redir(skibidishell);
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

static void	unlink_file(t_token *redir, t_skibidi *skibidishell)
{
	char	*heredoc_num;
	char	*heredoc_name;

	heredoc_num = ft_itoa(redir->here_doc);
	if (heredoc_num == NULL)
		ft_free_clean(skibidishell);
	heredoc_name = ft_strjoin("here_doc", heredoc_num);
	if (heredoc_name == NULL)
	{
		free(heredoc_num);
		ft_free_clean(skibidishell);
	}
	unlink(heredoc_name);
}

static void	unlink_heredoc(t_skibidi *skibidishell)
{
	t_token	*token;
	t_token	*redir;

	token = skibidishell->tokens;
	while (token)
	{
		if (token->type == HERE_DOC)
			unlink_file(token, skibidishell);
		redir = token->redir;
		while (redir)
		{
			if (redir->type == HERE_DOC)
				unlink_file(redir, skibidishell);
			redir = redir->next;
		}
		token = token->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_skibidi	*skibidishell;
	t_token		*token;
	char		*line;

	(void)argv;
	(void)argc;
	skibidishell = ft_calloc(1, sizeof(t_skibidi));
	if (!skibidishell)
		return (2);
	init_signals();
	if (!ft_export(skibidishell, envp) && reset_utils_env(&skibidishell->env))
	{
		line = ft_strdup("<< stop");
		// line = free_and_trim(readline(ft_get_prompt(g_signal)));
		while (line)
		{
			if (line[0])
			{
				g_signal = check_line(line);
				if (g_signal != 2)
				{
					add_history(line);
					handle_line(line, skibidishell);
					token = skibidishell->tokens;
					while (token)
					{
						if (token->type == STR)
							waitpid(token->pid->p_id, &token->pid->status, 0);
						token = token->next;
					}
				}
			}
			free(line);
			///
			unlink_heredoc(skibidishell);
			reset_utils_env(&skibidishell->env);
			line = free_and_trim(readline(ft_get_prompt(g_signal)));
		}
		perror(strerror(errno));
	}
	rl_clear_history();
	ft_free_clean(skibidishell);
	return (0);
}
