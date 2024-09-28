/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:36:33 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 19:02:50 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// Enums
typedef enum e_side			t_side;
typedef enum e_type			t_type;

// Structures
typedef struct s_pid		t_pid;
typedef struct s_env		t_env;
typedef struct s_string		t_string;
typedef struct s_token		t_token;
typedef struct s_kibidi		t_skibidi;

// ft_lexer.c
void		check_for_heredoc(t_skibidi *shell, t_token *token);
t_token		*ft_lexer(t_skibidi *shell, char *input);
void		merge_tokens(t_skibidi *shell, t_token **token, t_token *cmd);

// lx_lst_add.c
bool		is_word_delimiter(t_token **tokens, char *str, int *i);
bool		lx_createadd(t_skibidi *shell, t_token **tokens,
				char *input, int *i);

// lx_lst_manip.c
t_token		*lx_meta_token(t_skibidi *shell, char *str, int *i, int token_type);
t_token		*lx_str_token(t_skibidi *shell, char *str, int *i,
				int token_type);

// lx_manip_utils.c
char		*lx_strictstrdup(char *str, int *i);
char		*lx_strdup(char *str, int *i);
t_token		*lx_getlast(t_token *tokens);
void		lx_addback(t_token **tokens, t_token *ntoken);
void		lx_deltokens(t_token **tokens);

// lx_parentheses.c
void		to_close_parenthesis(char *str, int *i);
char		*trim_parentheses(char *str, int *i);

// lx_utils.c
int			is_sep(char *c);
int			which_token(t_token **tokens, char *c);

// merger_utils.c
t_token		get_next_token(t_token *token);
void		merge_redirection(t_skibidi *shell, t_token *current, t_token *cmd);
void		merge_arguments(t_skibidi *shell,
				t_token *current, t_token *cmd);
t_token		*get_cmd(t_token *token);
void		merge_operators(t_skibidi *shell, t_token *current);

// tstring_utils.c
t_string	*tstring_getlast(t_string *tstring);
void		tstring_addback(t_string **tstring, t_string *new_tstring);
void		tstring_del(t_string **tstring);
int			tstring_size(t_string **tstring);

// tstring.c
void		q_tstr(char *str, int *i, t_string **tstring);
void		other_tstr(char *str, int *i, int token_type, t_string **tstring);
t_string	*create_tstring(char *str, int *i, int token_type);

#endif
