/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:35:12 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/01 18:20:44 by mel-habi         ###   ########.fr       */
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

// check_exit.c
bool	check_exit(t_skibidi *shell, t_token *tree);

// exec_subshell.c
void	exec_parentheses(t_skibidi *shell, t_token *tree, int *pipetab,
			t_side side);

// exec_utils.c
void	update_error_code(t_skibidi *shell, int status, bool is_builtin);
char	**build_envp(t_env *env);
void	close_pipe(int pipefd[2]);

// execution.c
int		builtin_exec(t_skibidi	*shell, char	*cmd, char	**argv,
			bool in_child);
int		exec_cmd(t_skibidi *shell, t_token *tree, int *pipetab, t_side side);

// fd_manager.c
int		fd_manager(t_skibidi *shell, t_token *tree,
			int *pipetab, t_side side);

// ft_exec.c
bool	exec_tree(t_skibidi *shell, t_token *tree, int *pipetab, t_side side);
int		get_arg_nb(t_token *tokens);
void	add_every_wc(t_skibidi *shell, char **array,
			t_token *token, int *i);
void	add_args(t_skibidi *shell, char **array,
			t_token *arguments, int *i);

// get_fd.c
int		get_hd_fd(t_skibidi *shell, t_token *redirection);
int		get_fd(t_skibidi *shell, t_token *redirection);

// get_path.c
char	*get_pathname(t_skibidi *shell, char *cmd);

// here_doc.c
int		get_here_doc_content(t_skibidi *shell, t_token *tree);

// pid_list_manip.c
t_pid	*ft_lstnew_pipex(t_skibidi *shell);

#endif
