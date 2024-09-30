/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:29:12 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/30 16:43:37 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static int	ft_strncmp_pipex(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n < 1 || !s1)
		return (0);
	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static int	heredoc_creator(t_skibidi *shell, t_token *tree)
{
	int		i;
	int		fd_hd;
	char	*i_to_a;
	char	*hd_name;

	i = 0;
	fd_hd = open(".here_doc0", O_WRONLY | O_CREAT | O_EXCL, 0644);
	while (fd_hd == -1)
	{
		i++;
		i_to_a = ft_itoa(i);
		if (i_to_a == NULL)
			exit_shell(shell);
		hd_name = ft_strjoin(".here_doc", i_to_a);
		if (hd_name == NULL)
		{
			free(i_to_a);
			exit_shell(shell);
		}
		fd_hd = open(hd_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
		free(i_to_a);
		free(hd_name);
	}
	tree->here_doc = i;
	return (fd_hd);
}

static int	ghdc_end(char *limiter, int fd_hd,
	char *next_line)
{
	close(fd_hd);
	if (next_line == NULL)
	{
		ft_print_error(NULL, limiter,
			"the following heredoc limiter has been replaced by ctrl-d (EOF):",
			"\"\"");
		return (1);
	}
	free(next_line);
	return (0);
}

int	get_here_doc_content(t_skibidi *shell, t_token *tree)
{
	int		fd_hd;
	char	*next_line;
	char	*limiter;
	char	*tmp;

	limiter = tree->next->assembled;
	if (limiter == NULL)
		return (-1);
	fd_hd = heredoc_creator(shell, tree);
	next_line = readline("> ");
	while (!g_signal && next_line != NULL
		&& ft_strncmp_pipex(next_line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		next_line = exp_pos_param(shell, next_line);
		next_line = exp_env_var(shell, next_line);
		if (next_line == NULL)
			break ;
		tmp = next_line;
		next_line = ft_strjoin(tmp, "\n");
		free(tmp);
		write(fd_hd, next_line, ft_strlen(next_line));
		free(next_line);
		next_line = readline("> ");
	}
	return (ghdc_end(limiter, fd_hd, next_line));
}
