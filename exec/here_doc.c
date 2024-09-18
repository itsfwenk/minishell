/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:50:16 by fli               #+#    #+#             */
/*   Updated: 2024/09/18 14:18:46 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	heredoc_creator(t_token *tree, t_skibidi *skibidishell)
{
	int		i;
	int		fd_hd;
	char	*i_to_a;
	char	*hd_name;

	i = 0;
	fd_hd = open("here_doc0", O_CREAT | O_EXCL, 0644);
	while (fd_hd == -1)
	{
		i++;
		i_to_a = ft_itoa(i);
		if (i_to_a == NULL)
			ft_free_clean(skibidishell);
		hd_name = ft_strjoin("here_doc", i_to_a);
		if (hd_name == NULL)
		{
			free(i_to_a);
			ft_free_clean(skibidishell);
		}
		fd_hd = open(hd_name, O_CREAT | O_EXCL, 0644);
		free(i_to_a);
		free(hd_name);
	}
	tree->pid->here_doc = i;
	return (fd_hd);
}

int	get_here_doc_content(t_token *tree, t_skibidi *skibidishell)
{
	int		fd_hd;
	char	*next_line;
	char	*limiter;

	limiter = ft_strjoin(tree->next->assembled, "\n");
	if (limiter == NULL)
		return (-1);
	fd_hd = heredoc_creator(tree, skibidishell);
	next_line = readline("> ");
	while (next_line != NULL
		&& ft_strncmp_pipex(next_line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		if (next_line == NULL)
			break ;
		write(fd_hd, next_line, ft_strlen(next_line));
		free(next_line);
		next_line = readline("> ");
	}
	free(limiter);
	free(next_line);
	close(fd_hd);
	if (next_line == NULL)
		ft_free_clean(skibidishell); // include close fd
	return (0);
}
