/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:10:27 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/12 16:03:06 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_string
{
	char			*str;
	int				to_be_expanded;
	int				between_quote;
	struct s_string	*next;
}	t_string;

typedef struct s_token
{
	t_string		*tstring;
	t_string		*expanded_list; //	expanded + wildcarded	as a linked list
	char			*full_string; //	initial input
	char			*assembled; //		t_strings assembled			after expand (needed for wildcard)
	int				type;
	struct s_token	*arguments; //		arguments as tokens
	char			**argv; //			all arguments as an array	after expand and wildcards
	struct s_token	*infile; //
	struct s_token	*outfile; //
	struct s_token	*sub_shell;
	struct s_token	*next;
}	t_token;

typedef enum e_types
{
	PIPE,
	IN_REDIR,
	OUT_REDIR,
	OR,
	AND,
	APD_OUT_REDIR,
	HERE_DOC,
	STR,
	PAR_STR,
	FILENAME,
	HD_LIMITER,
}	t_types;

typedef struct s_leaf
{
	int				n_tokens;
	int				in;
	int				out;
	t_string		*infile;
	t_string		*outfile;
	t_token			*tokens;
	struct s_leaf	*left;
	struct s_leaf	*right;
}	t_leaf;


// typedef struct s_cmd_arg
// {
// 	t_string		*args;
// 	struct s_cmd_arg	*next;
// }	t_cmd_arg;

// typedef struct s_leaf
// {
// 	int				in;
// 	int				out;
// 	t_string		*infile;
// 	t_string		*outfile;
// 	t_cmd_arg		*cmd_arg;
// 	struct s_leaf	*left;
// 	struct s_leaf	*right;
// }	t_leaf;

// utils
int			is_word_delimiter(t_token **tokens, char *str, int i);
int			lx_createadd(t_token **tokens, char *str, int *i);
char		*lx_strdup(char *str, int *i);
char		*lx_strictstrdup(char *str, int *i); //
t_token		*lx_meta_token(char *str, int *i, int token_type);
t_token		*lx_str_token(t_token **tokens, char *str, int *i, int token_type);
t_token		*lx_getlast(t_token *tokens);
void		lx_addback(t_token **tokens, t_token *ntoken);
void		lx_deltokens(t_token **tokens);
void		to_close_parenthesis(char *str, int *i);
char		*trim_parentheses(char *str, int *i);
int			is_sep(char *c);
int			which_token(t_token **tokens, char *c);
t_string	*tstring_getlast(t_string *tstring);
void		tstring_addback(t_string **tstring, t_string *new_tstring);
void		tstring_del(t_string **tstring);
void		sq_tstr(char *str, int *i, t_string **tstring);
void		other_tstr(char *str, int *i, int token_type, t_string **tstring);
t_string	*create_tstring(char *str, int *i, int token_type);

t_token		*ft_lexer(char *input);

// EXPANDER FUNCTIONS

void	exp_pos_param(t_string *current);

#endif
