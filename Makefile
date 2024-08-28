# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/20 14:56:45 by mel-habi          #+#    #+#              #
#    Updated: 2024/08/28 15:57:04 by mel-habi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft

SOURCES		= minishell.c \
			  builtins/utils/bi_checkers.c builtins/utils/bi_env.c builtins/utils/bi_free.c \
			  builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_exit.c builtins/ft_export.c builtins/ft_pwd.c builtins/ft_unset.c \
			  lexer/utils/lx_lst_add.c lexer/utils/lx_lst_manip.c lexer/utils/lx_manip_utils.c lexer/utils/lx_parentheses.c lexer/utils/lx_utils.c lexer/utils/tstring_utils.c lexer/utils/tstring.c \
			  lexer/ft_lexer.c \
			  utils/ms_free.c utils/ms_print.c
OBJECTS		= $(SOURCES:.c=.o)

HEADERS		= minishell.h \
			  lexer/lexer.h \
			  builtins/builtins.h \
			  utils/ms_utils.h
FLAGS		= -Wall -Wextra -Werror
LIBS		= -L$(LIBFT) -lft -I$(LIBFT) -lreadline
OPTIONS		= -I$(LIBFT) -I. -Ibuiltins -Iutils

#################################################################################

RED 	 = '\033[0;31m'
GREEN 	 = '\033[0;32m'
YELLOW 	 = '\033[0;33m'
BLUE 	 = '\033[0;34m'
PURPLE 	 = '\033[0;35m'
NC 		 = '\033[0m'

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
