/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:51:25 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/23 10:29:13 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <dirent.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft/libft.h"

# include "builtins/builtins.h"
# include "lexer/lexer.h"
# include "utils/ms_utils.h"

# define FALSE 0
# define TRUE 1
# define METAS "|&<>"

# define LEFT 0
# define RIGHT 1

typedef struct s_pids
{
	// t_token			*token;
	int				status;
	int				pipefd[2];
	int				here_doc;
	pid_t			p_id;
	struct s_pids	*next;
}	t_pids;

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
	t_string		*expanded_list;//
	char			*full_string;
	char			*assembled;
	int				type;
	struct s_token	*arguments;
	char			**argv;
	struct s_token	*redir;
	struct s_token	*sub_shell;
	struct s_token	*next;
	struct s_token	*left;
	struct s_token	*right;
	t_pids			*pid;
	int				*previous_pipe;
	int				fd;
}	t_token;

typedef struct s_kibidi
{
	t_env	*env;
	t_token	*tokens;
	t_token	*tree;
}	t_skibidi;


extern int	g_signal;

int			exp_check_keys(t_string *current,
				t_skibidi *skibidishell, int *i, int *delta_char);
t_env		*key_exists(t_string *current, t_skibidi *skibidishell,
				int *limits);
void		exp_no_brackets(t_string *current,
				t_skibidi *skibidishell, int *i, int *delta_char);
int			exp_env_var(t_string *current, t_skibidi *skibidishell);
void		ft_expander(t_skibidi *skibidishell, t_token *token);
void		merge_tokens(t_skibidi *skibidishell, t_token **token,
				t_token *cmd);
void		merge_redirection(t_skibidi *skibidishell,
				t_token *current, t_token *cmd);
void		merge_arguments(t_skibidi *skibidishell,
				t_token *current, t_token *cmd);
t_token		*get_cmd(t_token *token);
void		merge_operators(t_skibidi *skibidishell, t_token *current);
int			ft_export(t_skibidi *skibidishell, char **args);
void		assemble_tstring(t_skibidi *skibidishell);
void		exp_pos_param(t_string *current, t_skibidi *skibidishell);
// void		create_argv(t_token *tokens, t_skibidi *skibidishell);
t_token		*lx_meta_token(char *str, int *i, int token_type,
				t_skibidi *skibidishell);
t_token		*lx_str_token(t_skibidi *skibidishell, char *str, int *i,
				int token_type);
int			lx_createadd(t_token **tokens, t_skibidi *skibidishell,
				char *input, int *i);
t_token		*ft_lexer(char *input, t_skibidi *skibidishell);

int			get_here_doc_content(t_token *tree, t_skibidi *skibidishell);

char		**build_envp(t_env *env);

int			exec_tree(t_skibidi *skibidishell, t_token *tree, int *pipetab, int side);


t_pids	*ft_lstnew_pipex(t_skibidi *skibidishell);
char	*get_pathname(t_skibidi *skibidishell, char *cmd);
void	get_filenames(t_token *tokens, t_skibidi *skibidishell);

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

// utils
int			is_word_delimiter(t_token **tokens, char *str, int i);
char		*lx_strictstrdup(char *str, int *i);
char		*lx_strdup(char *str, int *i);
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
void		q_tstr(char *str, int *i, t_string **tstring);
void		other_tstr(char *str, int *i, int token_type, t_string **tstring);
t_string	*create_tstring(char *str, int *i, int token_type);
int			tstring_size(t_string **tstring);

t_token		*create_tree(t_token *token);
int			check_syntax(t_token *tokens);

int			check_filename(t_token *tokens, char *filename, int i, int j);

t_token		*get_next_token(t_token *token);









void	ft_print_color(char *msg, char *color);
void	ft_print_error(char *cmd, char *arg, char *error, char *seps);
char	*ft_get_prompt(int err);
void	ft_free_clean(t_skibidi *skibidishell);
int		is_well_formated(char *str);
int		finished_by_meta(char *str);
int		is_brace_well_formated(char *str);
int		has_semicolon(char *str);

#endif
