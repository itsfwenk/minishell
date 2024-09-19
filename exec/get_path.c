/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:55:56 by fli               #+#    #+#             */
/*   Updated: 2024/09/19 15:31:51 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_pipex(char const *s1, char const *s2)
{
	int		tot;
	char	*joined;

	tot = ft_strlen(s1) + ft_strlen(s2) + 2;
	joined = malloc((tot) * sizeof(char));
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, ft_strlen(s1) + 1);
	joined[ft_strlen(joined) + 1] = '\0';
	joined[ft_strlen(joined)] = '/';
	ft_strlcat(joined, s2, tot);
	return (joined);
}

static char	**get_path_tab(t_skibidi *skibidishell)
{
	t_env		*path_var;
	char		**path_tab;

	path_var = get_env(skibidishell->env, "PATH");
	if (path_var == NULL)
		return (NULL);
	path_tab = ft_split(path_var->value, ":");
	if (path_tab == NULL)
		return (NULL);
	return (path_tab);
}

char	*get_pathname(t_skibidi *skibidishell, char *cmd)
{
	int		i;
	char	**path_tab;
	char	*path_cmd;

	if (cmd == NULL)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	path_tab = get_path_tab(skibidishell);
	if (path_tab == NULL)
		return (NULL);
	i = 0;
	while (path_tab[i] != NULL)
	{
		path_cmd = ft_strjoin_pipex(path_tab[i], cmd);
		if (path_cmd == NULL)
			return (free_all(path_tab), ft_free_clean(skibidishell), NULL);
		if (access(path_cmd, X_OK) == 0)
			return (free_all(path_tab), path_cmd);
		i++;
		free(path_cmd);
	}
	free_all(path_tab);
	return (NULL);
}
