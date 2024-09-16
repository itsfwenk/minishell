/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:27:45 by fli               #+#    #+#             */
/*   Updated: 2024/09/16 17:58:15 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_to_expanded_list(t_token *tokens, char *filename)
{
	t_string		*new_tstring;

	new_tstring = malloc(sizeof(t_string));
	if (new_tstring == NULL)
		return ;
	new_tstring->str = ft_strdup(filename);
	if (new_tstring->str == NULL)
		return ;
	new_tstring->to_be_expanded = -1;
	new_tstring->between_quote = -1;
	new_tstring->next = NULL;
	tstring_addback(&tokens->expanded_list, new_tstring);
}

void	get_filenames(t_token *tokens)
{
	DIR				*directory;
	struct dirent	*read_return;

	directory = opendir(".");
	read_return = readdir(directory);
	while (read_return != NULL)
	{
		if (check_filename(tokens, read_return->d_name, 0, 0))
			add_to_expanded_list(tokens, read_return->d_name);
		else
			add_to_expanded_list(tokens, tokens->assembled);
	}
	closedir(directory);
}

static int	get_arg_nb(t_token *tokens)
{
	int		i;
	t_token	*arguments;

	i = 0;
	arguments = tokens->arguments;
	while (arguments != NULL)
	{
		i = i + tstring_size(&arguments->expanded_list);
		arguments = arguments->next;
	}
	return (i);
}

void	create_argv(t_token *tokens)
{
	int			i;
	char		**array;
	t_token		*arguments;
	t_string	*expanded_list;

	array = ft_calloc(get_arg_nb(tokens) + 1, sizeof(char *));
	if (array == NULL)
		return ;
	i = 0;
	arguments = tokens->arguments;
	while (arguments != NULL)
	{
		expanded_list = arguments->expanded_list;
		while (expanded_list != NULL)
		{
			array[i] = ft_strdup(expanded_list->str);
			if (array[i] == NULL)
				return ;
			expanded_list = expanded_list->next;
			i++;
		}
		arguments = arguments->next;
	}
	tokens->argv = array;
}
