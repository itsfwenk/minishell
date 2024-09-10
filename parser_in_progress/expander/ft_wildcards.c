/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:27:45 by fli               #+#    #+#             */
/*   Updated: 2024/09/10 17:25:21 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	check_filename(char *wc, char *filename, int i, int j)
// {
// 	int	k;

// 	k = 0;
// 	while (wc[i + k] != '\0')
// 	{
// 		if (wc[i + k] == '*')
// 		{
// 			i++;
// 			if (wc[i] == '\0')
// 				return (TRUE);
// 			while (wc[i + k] != '\0' && filename[j + k] != '\0'
// 				&& wc[i] != filename[j])
// 			{
// 				if (wc[i] == '*')
// 					return (check_filename(wc, filename, i + k, j + k));
// 				j++;
// 			}
// 		}
// 		while (wc[i + k] != '\0' && filename[j + k] != '\0')
// 		{
// 			if (wc[i + k] == '*')
// 			{
// 				if (check_filename(wc, filename, i + k, j + k) == TRUE)
// 					return (TRUE);
// 				j++;
// 				k = 0;
// 			}
// 			else if (wc[i + k] == filename[j + k])
// 				k++;
// 			else
// 			{
// 				k = 0;
// 				j++;
// 			}
// 		}
// 		if ((wc[i + k] != '\0' || filename[j + k] != '\0') && wc[i + k] != '*')
// 			return (FALSE);
// 	}
// 	return (TRUE);
// }


// int	check_filename(char *wc, char *filename, int i, int j)
// {
// 	if (wc[i] == '\0' && filename[j] == '\0')
// 		return (TRUE);
// 	if (wc[i] == '*')
// 	{
// 		if (check_filename(wc, filename, i + 1, j) == TRUE);
// 			return (TRUE);
// 		return (check_filename(wc, filename, i, j + 1));
// 	}
// 	if (wc[i] == filename[j])
// 		return (check_filename(wc, filename, i + 1, j + 1));
// 	return (FALSE);
// }

int check_filename(char *wc, char *filename, int i, int j)
{
	while (wc[i] != '\0')
	{
		if (wc[i] == '*')
		{
			i++;
			if (wc[i] == '\0')
				return (TRUE);
			while (filename[j] != '\0')
			{
				if (check_filename(wc, filename, i, j) == TRUE)
					return (TRUE);
				j++;
			}
			return (FALSE);
		}
		else if (wc[i] != filename[j])
			return (FALSE);
		i++;
		j++;
	}
	return (filename[j] == '\0');
}

char	*get_filenames(t_string *current)
{
	t_string		*filenames;
	DIR				*directory;
	struct	dirent	*read_return;

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
