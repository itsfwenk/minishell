/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:46:38 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/29 10:33:57 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	sigint(int status)
{
	(void)status;
	g_signal = 130;
	ft_putchar_fd('\n', STDIN_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	no_behaviour(void)
{
	return (EXIT_SUCCESS);
}

void	exec_sig(int status)
{
	(void)status;
	g_signal = 130;
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	heredoc_sig(int status)
{
	(void)status;
	g_signal = 130;
	rl_done = 1;
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	rl_event_hook = no_behaviour;
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
