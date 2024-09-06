/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:27:45 by fli               #+#    #+#             */
/*   Updated: 2024/09/06 18:57:04 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_filenames(t_string *current)
{
	char	*filenames;
	DIR		*directory;
	struct	dirent *read_return;

	directory = opendir(".");
	read_return = readdir(directory);
	while (read_return != NULL)
	{
		printf("%s\n", read_return->d_name);
		read_return = readdir(directory);
	}
	closedir(directory);
}

void	ft_wildcards(t_skibidi *skibidishell)
{
	int			i;
	t_token		*tokens;
	t_string	*current_tstr;

	tokens = skibidishell->tokens;
	while (tokens != NULL)
	{
		current_tstr = tokens->tstring;
		while (current_tstr != NULL)
		{
			if (current_tstr->between_quote == FALSE)
			{
				i = 0;
				while (current_tstr->str[i] != '\0')
				{
					if (current_tstr->str[i] == '*')
						get_filenames(current_tstr);
				}
			}
			current_tstr = current_tstr->next;
		}
		tokens = tokens->next;
	}
}
