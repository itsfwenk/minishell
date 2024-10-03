/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:29:12 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 00:25:12 by mel-habi         ###   ########.fr       */
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

	i = 1;
	fd_hd = open(".here_doc1", O_WRONLY | O_CREAT | O_EXCL, 0644);
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

static int	ghdc_end(t_skibidi *shell, char *limiter, int fd_hd,
	char *next_line)
{
	update_error_code(shell, g_signal.code, false);
	close(fd_hd);
	if (next_line == NULL)
	{
		ft_print_error(NULL, limiter,
			"the following heredoc limiter has been replaced by ctrl-d (EOF):",
			"\"\"");
		return (1);
	}
	free(next_line);
	free(limiter);
	return (0);
}

static char	*check_expand(t_skibidi *shell, t_token *tree, char *line)
{
	char	*next_line;

	if (ft_strchr(tree->next->full_string, '\'')
		|| ft_strchr(tree->next->full_string, '"'))
		return (line);
	next_line = exp_pos_param(shell, line);
	next_line = exp_env_var(shell, line);
	return (next_line);
}

int	get_here_doc_content(t_skibidi *shell, t_token *tree)
{
	int		fd_hd;
	char	*next_line;
	char	*limiter;
	char	*tmp;

	limiter = get_limiter(shell, tree->next);
	if (limiter == NULL)
		return (-1);
	fd_hd = heredoc_creator(shell, tree);
	next_line = readline("> ");
	while (!g_signal.code && next_line != NULL
		&& ft_strncmp_pipex(next_line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		next_line = check_expand(shell, tree, next_line);
		if (next_line == NULL)
			break ;
		tmp = next_line;
		next_line = ft_strjoin(tmp, "\n");
		free(tmp);
		write(fd_hd, next_line, ft_strlen(next_line));
		free(next_line);
		next_line = readline("> ");
	}
	return (ghdc_end(shell, limiter, fd_hd, next_line));
}
