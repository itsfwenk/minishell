/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:27:12 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 20:42:02 by mel-habi         ###   ########.fr       */
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

static void	wait_children(t_skibidi *shell)
{
	t_token		*token;

	token = shell->tokens;
	while (token)
	{
		if (token->type == STR && token->pid)
			waitpid(token->pid->p_id, &token->pid->status, 0);
		token = token->next;
	}
}

static void	skibidi_loop(t_skibidi *shell)
{
	char	*line;

	while (1)
	{
		line = readline(ft_get_prompt(!!shell->exit_code));
		if (!line)
			break ;
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

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (shell)
	{
		ft_print_logo();
		skibidi_loop(shell);
	}
	ft_putendl_fd("exit", 2);
	return (exit_shell(shell));
}
