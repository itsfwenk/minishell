/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:35:12 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/07 13:27:08 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// Enums
typedef enum e_side			t_side;
typedef enum e_type			t_type;

// Structures
typedef struct s_pid		t_pid;
typedef struct s_env		t_env;
typedef struct s_string		t_string;
typedef struct s_token		t_token;
typedef struct s_kibidi		t_skibidi;
typedef struct s_pipe		t_pipe;

// check_exit.c
void	check_cmd_path(t_skibidi *shell, t_token *tree, char *cmd_path);
bool	check_exit(t_skibidi *shell, t_token *tree, int *pipetab, t_side side);

// cmd_err_utils.c
void	cmd_not_found(t_skibidi *shell, t_token *tree, char *cmd_path);
void	cmd_no_perm(t_skibidi *shell, t_token *tree, char *cmd_path);

// exec_subshell.c
void	exec_parentheses(t_skibidi *shell, t_token *tree, int *pipetab,
			t_side side);

// exec_utils.c
void	update_error_code(t_skibidi *shell, int status, bool is_builtin);
char	**build_envp(t_env *env);
void	close_pipe(int pipefd[2]);

// execution.c
int		builtin_exec(t_skibidi	*shell, char	*cmd, char	**argv,
			bool in_pipe);
void	add_args(t_skibidi *shell, char **array,
			t_token *arguments, int *i);
int		exec_cmd(t_skibidi *shell, t_token *tree, int *pipetab, t_side side);

// fd_manager.c
bool	dup_fd(int fd_redir, t_token *redirection);
bool	file_access_fail(t_skibidi *shell, t_token *redirection);
int		fd_manager(t_skibidi *shell, t_token *tree,
			int *pipetab, t_side side);

// ft_exec.c
bool	exec_tree(t_skibidi *shell, t_token *tree, int *pipetab, t_side side);
int		get_arg_nb(t_token *tokens);
void	add_every_wc(t_skibidi *shell, char **array,
			t_token *token, int *i);

// get_fd.c
int		get_hd_fd(t_skibidi *shell, t_token *redirection);
int		get_fd(t_skibidi *shell, t_token *redirection);

// get_path.c
char	*get_pathname(t_skibidi *shell, char *cmd);

// here_doc_utils.c
char	*get_limiter(t_skibidi *shell, t_token *limiter_token);

// here_doc.c
int		get_here_doc_content(t_skibidi *shell, t_token *tree);

// pid_list_manip.c
t_pid	*ft_lstnew_pipex(t_skibidi *shell);

// pipe_utils.c
void	pipe_manager(t_skibidi *shell, t_token *tree,
			int *pipetab, t_side side);
void	close_garbage(t_pipe *garbage);
void	free_tpipe(t_pipe *to_free);

#endif
