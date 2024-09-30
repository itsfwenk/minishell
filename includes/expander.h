/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:35:35 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/30 14:13:05 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

// Enums
typedef enum e_side			t_side;
typedef enum e_type			t_type;

// Structures
typedef struct s_pid		t_pid;
typedef struct s_env		t_env;
typedef struct s_string		t_string;
typedef struct s_token		t_token;
typedef struct s_kibidi		t_skibidi;

// assemble_tstring.c
void	assemble_tstring(t_skibidi *shell, t_token *token);

// check_filename.c
bool	check_filename(t_token *tokens, char *filename, int i, int j);

// exp_delta_in_brackets.c
bool	exp_check_keys(t_skibidi *shell, char *str,
			int *i, int *delta_char);

// exp_delta_no_brackets.c
t_env	*key_exists(t_skibidi *shell, char *str, int *limits);
void	exp_no_brackets(t_skibidi *shell, char *str,
			int *i, int *delta_char);

// exp_env_var.c
char	*exp_env_var(t_skibidi *shell, char *str);

// exp_pos_param.c
char	*exp_pos_param(t_skibidi *shell, char *str);

// ft_expander.c
bool	ft_expander(t_skibidi *shell, t_token *token);

// ft_wildcards.c
void	get_filenames(t_skibidi *shell, t_token *tokens);

#endif
