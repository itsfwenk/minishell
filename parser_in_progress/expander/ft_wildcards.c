/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:27:45 by fli               #+#    #+#             */
/*   Updated: 2024/09/11 18:57:43 by fli              ###   ########.fr       */
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

// int check_filename(char *wc, char *filename, int i, int j)
// {
// 	while (wc[i] != '\0')
// 	{
// 		if (wc[i] == '*')
// 		{
// 			i++;
// 			if (wc[i] == '\0')
// 				return (TRUE);
// 			while (filename[j] != '\0')
// 			{
// 				if (check_filename(wc, filename, i, j) == TRUE)
// 					return (TRUE);
// 				j++;
// 			}
// 			return (FALSE);
// 		}
// 		else if (wc[i] != filename[j])
// 			return (FALSE);
// 		i++;
// 		j++;
// 	}
// 	return (filename[j] == '\0');
// }

int	is_literal(t_token *tokens, int	i)
{
	int			j;
	int			k;
	t_string	*current;

	j = 0;
	current = tokens->tstring;
	while (current != NULL)
	{
		k = 0;
		while (current->str[k] != '\0')
		{
			if (j = i)
				return(current->between_quote == TRUE);
			j++;
			k++;
		}
		current = tokens->tstring;
	}
	return (FALSE);
}

int	check_filename(t_token *tokens, char *filename, int i, int j)
{
	if (tokens->assembled[i] == '\0' && filename[j] == '\0')
		return (TRUE);
	if (tokens->assembled[i] == '*' && !is_literal(tokens, i))
	{
		if (check_filename(tokens, filename, i + 1, j) == TRUE);
			return (TRUE);
		return (check_filename(tokens, filename, i, j + 1));
	}
	if (tokens->assembled[i] == filename[j])
		return (check_filename(tokens, filename, i + 1, j + 1));
	return (FALSE);
}

void	add_to_expanded_list(t_token *tokens, char *filename)
{
	t_string		*new_tstring;

	new_tstring = malloc(sizeof(t_string));
	if (new_tstring == NULL)
		return ; //ft_exit_clean
	new_tstring->str = ft_strdup(filename);
	if (new_tstring->str == NULL)
		return ; //ft_exit_clean
	new_tstring->to_be_expanded = -1;
	new_tstring->between_quote = -1;
	new_tstring->next == NULL;
	tstring_addback(&tokens->expanded_list, new_tstring);
}

void	get_filenames(t_token *tokens)
{
	t_string		*filenames;
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

int	get_arg_nb(t_token *tokens)
{
	int		i;
	t_token	*arguments;

	i = 0;
	arguments = tokens->arguments;
	while (arguments != NULL)
	{
		i = i + tstring_size(arguments->expanded_list);
		arguments = arguments->next;
	}
	return (i);
}

void	create_argv(t_token *tokens)
{
	int			i;
	char		**array;
	t_token 	*arguments;
	t_string	*expanded_list;

	array = ft_calloc(get_arg_nb(tokens) + 1, sizeof(char *));
	if (array == NULL)
		return ; //ft_exit_clean
	i = 0;
	arguments = tokens->arguments;
	while (arguments != NULL)
	{
		expanded_list = arguments->expanded_list;
		while (expanded_list != NULL)
		{
			array[i] = ft_strdup(expanded_list->str);
			if (array[i] == NULL)
				return ; //ft_exit_clean
			expanded_list = expanded_list->next;
			i++;
		}
		arguments = arguments->next;
	}
	tokens->argv = array;
}

// void	ft_wildcards(t_skibidi *skibidishell)
// {
// 	int			i;
// 	int			j;
// 	t_token		*tokens;
// 	t_string	*current_tstr;

// 	tokens = skibidishell->tokens;
// 	while (tokens != NULL)
// 	{
// 		current_tstr = tokens->tstring;
// 		if (current_tstr->between_quote == FALSE)
// 		{
// 			i = 0;
// 				while (current_tstr->str[i] != '\0')
// 				{
// 					if (current_tstr->str[i] == '*')
// 						get_filenames(current_tstr);
// 				}
// 			}
// 			current_tstr = current_tstr->next;
// 		}
// 		tokens = tokens->next;
// }
