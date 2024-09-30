/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:11:25 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/30 16:30:14 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	add_to_wildcard_list(t_skibidi *shell,
	t_token *tokens, char *filename)
{
	t_string		*new_tstring;

	new_tstring = ft_calloc(1, sizeof(t_string));
	if (new_tstring == NULL)
		exit_shell(shell);
	new_tstring->str = ft_strdup(filename);
	if (new_tstring->str == NULL)
		exit_shell(shell);
	new_tstring->to_be_expanded = false;
	new_tstring->between_quote = false;
	new_tstring->next = NULL;
	tstring_addback(&tokens->wildcard_list, new_tstring);
}

static void	get_arg_redir_filenames(t_skibidi *shell, t_token *tokens)
{
	t_token	*current;

	if (tokens->type == FILENAME && tokens->wildcard_list->next != NULL)
	{
		ft_print_error(NULL, tokens->full_string, "ambiguous redirect ඞ",
			"\"\"");
		return ;
	}
	current = tokens->arguments;
	while (current)
	{
		get_filenames(shell, current);
		current = current->next;
	}
	current = tokens->redir;
	while (current)
	{
		if (current->type == HD_LIMITER)
		{
			current = current->next;
			continue;
		}
		get_filenames(shell, current);
		current = current->next;
	}
}

void	get_filenames(t_skibidi *shell, t_token *tokens)
{
	DIR				*directory;
	struct dirent	*read_return;

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
		if (check_filename(tokens, read_return->d_name, 0, 0) == true)
			add_to_wildcard_list(shell, tokens, read_return->d_name);
		read_return = readdir(directory);
	}
	if (tokens->wildcard_list == NULL)
		add_to_wildcard_list(shell, tokens, tokens->assembled);
	closedir(directory);
	get_arg_redir_filenames(shell, tokens);
	return ;
}
