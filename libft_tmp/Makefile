# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 10:07:51 by mel-habi          #+#    #+#              #
#    Updated: 2024/09/28 19:52:58 by mel-habi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		  ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		  ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
		  ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
		  ft_atoi.c ft_itoa.c ft_tolower.c ft_toupper.c \
		  ft_dprintf.c
OBJECTS = $(SOURCES:.c=.o)

BONUS_SOURCES = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstnew_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstsize_bonus.c
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

FLAGS = -Wall -Wextra -Werror
OPTIONS = -c -I .

#################################################################################

RED = '\033[0;31m'
GREEN = '\033[0;32m'
YELLOW = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
NC = '\033[0m'

#################################################################################

%.o: %.c
	@$(CC) $(FLAGS) $(OPTIONS) $< -o $@
	@echo $(GREEN)✅ $< compiled! $(NC)

$(NAME): $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)
	@echo $(BLUE)✅ $@ built! $(NC)

bonus: $(OBJECTS) $(BONUS_OBJECTS)
	@ar rcs $(NAME) $(OBJECTS) $(BONUS_OBJECTS)
	@echo $(PURPLE)✅ $(NAME) with bonus built! $(NC)

all: $(NAME)

clean:
	@rm -f $(OBJECTS) $(BONUS_OBJECTS)
	@echo $(YELLOW)🗑️ $(OBJECTS) $(BONUS_OBJECTS) deleted! $(NC)

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)🗑️ $(NAME) deleted! $(NC)

re: fclean all

.PHONY: all clean fclean re
