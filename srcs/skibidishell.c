/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:27:12 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/30 12:06:37 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

int	g_signal = 0;

static void	handle_line(t_skibidi *shell, char *line)
{
	shell->tokens = ft_lexer(shell, line);
	free(line);
	if (!shell->tokens || !check_syntax(shell, shell->tokens))
		return ;
	if (g_signal)
	{
		shell->exit_code = shell->exit_code + g_signal;
		g_signal = 0;
	}
	if (!only_redirs(shell->tokens))
	{
		merge_tokens(shell, &(shell->tokens), NULL);
		shell->tree = create_tree(shell->tokens);
		exec_tree(shell, shell->tree, NULL, -1);
	}
	else
	{
		expd_wc_only_redir(shell);
		check_for_here_doc(shell);
		open_only_redir(shell);
	}
	return ;
}

static void wait_children2(t_skibidi *shell, t_token *token)
{
	if (WIFEXITED(token->pid->status))
	{
		g_signal = 0;
		shell->exit_code = WEXITSTATUS(token->pid->status);
	}
	else if (WIFSIGNALED(token->pid->status))
	{
		if (WTERMSIG(token->pid->status) == SIGQUIT)
			ft_dprintf(2, "Quit (core dumped)\n");
		g_signal = 128 + WTERMSIG(token->pid->status);
	}
}
static void	wait_children(t_skibidi *shell)
{
	char	*itoa_return;
	t_token	*token;

	token = shell->tokens;
	signal(SIGQUIT, SIG_IGN);
	while (token)
	{
		if (token->type == STR && token->pid)
		{
			if (waitpid(token->pid->p_id, &token->pid->status, 0))
				wait_children2(shell, token);
			itoa_return = ft_itoa(g_signal + shell->exit_code);
			if (!itoa_return)
				exit_shell(shell);
			add_env(&shell->env, "?", itoa_return);
			free(itoa_return);
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
		line = readline(ft_get_prompt(!!(g_signal + shell->exit_code)));
		if (!line)
			break ;
		else if (!line[0])
			shell->exit_code = shell->exit_code;
		else if (!check_line(line))
			shell->exit_code = 2;
		else
		{
			shell->exit_code = 0;
			add_history(line);
			handle_line(shell, line);
			wait_children(shell);
			unlink_heredoc(shell);
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
	t_stat		prog_stat;

	(void)argc;
	(void)argv;
	fstat(STDOUT_FILENO, &prog_stat);
	if (S_ISFIFO(prog_stat.st_mode))
		return (EXIT_FAILURE);
	shell = init_shell(envp);
	if (shell)
	{
		ft_print_logo();
		skibidi_loop(shell);
	}
	ft_putendl_fd("exit", 2);
	return (exit_shell(shell));
}
