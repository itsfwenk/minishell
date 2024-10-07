/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:27:12 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/07 15:29:45 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

t_signal	g_signal = {0};

static void	create_all_hd(t_skibidi *shell, t_token *token)
{
	if (!token)
		return ;
	if (token->type == STR || token->type == PAR_STR)
		check_for_heredoc(shell, token);
	if (token->type == PAR_STR)
		check_for_here_doc(shell, token->sub_shell);
	create_all_hd(shell, token->left);
	create_all_hd(shell, token->right);
}

static void	handle_line(t_skibidi *shell, char *line)
{
	shell->stdin_save = dup(STDIN_FILENO);
	shell->stdout_save = dup(STDOUT_FILENO);
	if (shell->tokens)
		lx_deltokens(&shell->tokens);
	shell->tokens = ft_lexer(shell, line);
	free(line);
	if (!shell->tokens || !check_syntax(shell, shell->tokens))
		return ;
	if (!only_redirs(shell->tokens))
	{
		merge_tokens(shell, &(shell->tokens), NULL, false);
		shell->tree = create_tree(shell->tokens);
		create_all_hd(shell, shell->tree);
		exec_tree(shell, shell->tree, NULL, -1);
	}
	else
	{
		if (expd_wc_only_redir(shell, shell->tokens) == false)
			return ;
		check_for_here_doc(shell, shell->tokens);
		open_only_redir(shell, shell->tokens);
	}
	return ;
}

static void	wait_children(t_skibidi *shell)
{
	t_token	*token;

	token = shell->tokens;
	signal(SIGQUIT, SIG_IGN);
	while (token)
	{
		if ((token->type == STR || token->type == PAR_STR) && token->pid)
		{
			if (waitpid(token->pid->p_id, &token->pid->status, 0) != -1)
				update_error_code(shell, token->pid->status, false);
		}
		token = token->next;
	}
}

static void	skibidi_loop(t_skibidi *shell)
{
	char	*line;

	while (1)
	{
		init_signals();
		line = readline(ft_get_prompt(g_signal.code || shell->exit_code));
		if (!line)
			break ;
		else if (!line[0])
			shell->exit_code = shell->exit_code;
		else if (!check_line(line))
			syntax_error_reset(shell);
		else
		{
			add_history(line);
			handle_line(shell, line);
			wait_children(shell);
			unlink_heredoc(shell, shell->tokens);
			g_signal.heredoc_sigint = false;
			line = NULL;
		}
		if (line)
			free(line);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_skibidi	*shell;

	(void)argc;
	if (!isatty(STDIN_FILENO))
	{
		ft_print_error(argv[0], NULL, "Can\'t be executed on pipe \
(Not supported).", NULL);
		return (EXIT_FAILURE);
	}
	shell = init_shell(envp);
	if (shell)
	{
		ft_print_logo();
		skibidi_loop(shell);
		close(shell->stdin_save);
		close(shell->stdout_save);
	}
	ft_putendl_fd("exit", 2);
	return (exit_shell(shell));
}
