# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 23:15:10 by mel-habi          #+#    #+#              #
#    Updated: 2024/09/29 10:06:08 by mel-habi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell
LIBFT			= libft

BUILTINS_SRCS	= bi_checkers.c bi_env.c ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c
EXEC_SRCS		= exec_subshell.c exec_utils.c execution.c fd_manager.c ft_exec.c get_fd.c get_path.c here_doc.c pid_list_manip.c
EXPANDER_SRCS	= assemble_tstring.c check_filename.c exp_delta_in_brackets.c exp_delta_no_brackets.c exp_env_var.c exp_pos_param.c ft_expander.c ft_wildcards.c
LEXER_SRCS		= ft_lexer.c lx_lst_add.c lx_lst_manip.c lx_manip_utils.c lx_parentheses.c lx_utils.c merger_utils.c tstring_utils.c tstring.c
PARSER_SRCS		= check_syntax.c tree.c
SIGNALS_SRCS	= ft_signals.c
UTILS_SRCS		= char_utils.c free_utils.c init_utils.c line_utils.c only_redirs_utils.c print_utils.c str_utils.c syntax_checker_utils.c unlink_hd.c
MAIN_SRCS		= skibidishell.c

SOURCES			= $(addprefix srcs/builtins/, $(BUILTINS_SRCS)) \
				  $(addprefix srcs/exec/, $(EXEC_SRCS))	\
				  $(addprefix srcs/expander/, $(EXPANDER_SRCS)) \
				  $(addprefix srcs/lexer/, $(LEXER_SRCS)) \
				  $(addprefix srcs/parser/, $(PARSER_SRCS)) \
				  $(addprefix srcs/signals/, $(SIGNALS_SRCS)) \
				  $(addprefix srcs/utils/, $(UTILS_SRCS)) \
				  $(addprefix srcs/, $(MAIN_SRCS))
OBJECTS			= $(SOURCES:.c=.o)

HEADERS_FILES	= builtins.h exec.h expander.h lexer.h parser.h signals.h skibidishell.h utils.h
HEADERS			= $(addprefix includes/, $(HEADERS_FILES))
FLAGS			= -Wall -Wextra -Werror -g3
LIBS			= -L$(LIBFT) -lft -I$(LIBFT) -lreadline
OPTIONS			= -I$(LIBFT) -Iincludes/

#################################################################################

RED 	 		= '\033[0;31m'
GREEN 	 		= '\033[0;32m'
YELLOW 	 		= '\033[0;33m'
BLUE 	 		= '\033[0;34m'
PURPLE 	 		= '\033[0;35m'
NC 		 		= '\033[0m'

#################################################################################

%.o: %.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(OPTIONS) $< -o $@
	@echo $(GREEN)✅ $< compiled! $(NC)

$(NAME): $(LIBFT)/$(LIBFT).a $(OBJECTS) $(HEADERS)
	@$(CC) $(FLAGS) $(OPTIONS) -o $@ $(OBJECTS) $(LIBS)
	@echo $(BLUE)✅ $@ built! $(NC)

all: $(NAME)

clean:
	@rm -f $(OBJECTS)
	@make clean -C $(LIBFT)
	@echo $(YELLOW)🗑️ $(LIBFT) $(OBJECTS) deleted! $(NC)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@echo $(RED)🗑️ $(NAME) deleted! $(NC)

re: fclean all

$(LIBFT)/$(LIBFT).a: 
	@make -C $(LIBFT)
	@echo $(PURPLE)✅ $@ compiled! $(NC)

.PHONY: all clean fclean re
