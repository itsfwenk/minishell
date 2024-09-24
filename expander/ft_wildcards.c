/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:27:45 by fli               #+#    #+#             */
/*   Updated: 2024/09/24 11:26:19 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_to_wildcard_list(t_token *tokens, char *filename,
	t_skibidi *skibidishell)
{
	t_string		*new_tstring;

	new_tstring = malloc(sizeof(t_string));
	if (new_tstring == NULL)
		ft_free_clean(skibidishell);
	new_tstring->str = ft_strdup(filename);
	if (new_tstring->str == NULL)
		ft_free_clean(skibidishell);
	new_tstring->to_be_expanded = -1;
	new_tstring->between_quote = -1;
	new_tstring->next = NULL;
	tstring_addback(&tokens->wildcard_list, new_tstring);
}

void	get_filenames(t_token *tokens, t_skibidi *skibidishell)
{
	DIR				*directory;
	struct dirent	*read_return;
	t_token			*current;

	if (tokens == NULL)
		return ;
	directory = opendir(".");
	read_return = readdir(directory);
	while (read_return != NULL)
	{
		if (read_return->d_name[0] == '.')
		{
			read_return = readdir(directory);
			continue ;
		}
		if (check_filename(tokens, read_return->d_name, 0, 0))
			add_to_wildcard_list(tokens, read_return->d_name, skibidishell);
		read_return = readdir(directory);
	}
	if (tokens->wildcard_list == NULL)
		add_to_wildcard_list(tokens, tokens->assembled, skibidishell);
	closedir(directory);
	if (tokens->type == FILENAME && tokens->wildcard_list->next != NULL)
	{
		dprintf(2, "ambigous\n");
	}
	current = tokens->arguments;
	while (current)
	{
		get_filenames(current, skibidishell);
		current = current->next;
	}
	current = tokens->redir;
	while (current)
	{
		get_filenames(current, skibidishell);
		current = current->next;
	}
}

// static int	get_arg_nb(t_token *tokens)
// {
// 	int		i;
// 	t_token	*arguments;

// 	i = 0;
// 	arguments = tokens->arguments;
// 	while (arguments != NULL)
// 	{
// 		i = i + tstring_size(&arguments->expanded_list);
// 		arguments = arguments->next;
// 	}
// 	return (i);
// }

// static void	add_args(char **array, t_token *arguments,
// t_skibidi *skibidishell)
// {
// 	int			i;
// 	t_string	*expanded_list;

// 	i = 1;
// 	while (arguments != NULL)
// 	{
// 		expanded_list = arguments->expanded_list;
// 		while (expanded_list != NULL)
// 		{
// 			array[i] = ft_strdup(expanded_list->str);
// 			if (array[i] == NULL)
// 			{
// 				free_all(array);
// 				ft_free_clean(skibidishell);
// 			}
// 			expanded_list = expanded_list->next;
// 			i++;
// 		}
// 		arguments = arguments->next;
// 	}
// }

// void	create_argv(t_token *tokens, t_skibidi *skibidishell)
// {
// 	char		**array;
// 	t_token		*arguments;

// 	array = ft_calloc(get_arg_nb(tokens) + 2, sizeof(char *));
// 	if (array == NULL)
// 		ft_free_clean(skibidishell);
// 	arguments = tokens->arguments;
// 	array[0] = ft_strdup(tokens->assembled);
// 	if (array[0] == NULL)
// 	{
// 		free_all(array);
// 		ft_free_clean(skibidishell);
// 	}
// 	add_args(array, arguments, skibidishell);
// 	tokens->argv = array;
// }
