/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:28:31 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/05 10:15:51 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKIBIDISHELL_H
# define SKIBIDISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <stdlib.h>
# include <dirent.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft.h"

# include "builtins.h"
# include "exec.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "signals.h"
# include "utils.h"

// Enums
typedef enum e_side
{
	LEFT,
	RIGHT
}	t_side;

typedef enum e_type
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
}	t_type;

// Globale
typedef struct s_ignal
{
	int		code;
	bool	heredoc_sigint;
}	t_signal;

extern t_signal				g_signal;

// Structures
typedef struct s_pid		t_pid;
typedef struct s_env		t_env;
typedef struct s_string		t_string;
typedef struct s_token		t_token;

typedef struct s_pid
{
	int		status;
	int		pipefd[2];
	int		here_doc;
	pid_t	p_id;
	t_pid	*next;
}	t_pid;

typedef struct s_env
{
	char	*key;
	char	*value;
	bool	is_exported;
	bool	is_unset;
	t_env	*next;
}	t_env;

typedef struct s_string
{
	char		*str;
	bool		to_be_expanded;
	bool		between_quote;
	t_string	*next;
}	t_string;

typedef struct s_pipe
{
	int		*pipefd;
	t_pipe	*next;
}	t_pipe;

typedef struct s_token
{
	int			fd;
	int			here_doc;
	int			*previous_pipe;
	char		*assembled;
	char		*full_string;
	char		**argv;
	t_type		type;
	t_string	*tstring;
	t_string	*wildcard_list;
	t_pid		*pid;
	t_pipe		*garbage_pipe;
	t_token		*arguments;
	t_token		*redir;
	t_token		*sub_shell;
	t_token		*left;
	t_token		*right;
	t_token		*next;
}	t_token;

typedef struct s_kibidi
{
	int		exit_code;
	int		stdin_save;
	int		stdout_save;
	bool	to_exit;
	bool	in_par;
	t_env	*env;
	t_token	*tokens;
	t_token	*tree;
}	t_skibidi;

#endif
