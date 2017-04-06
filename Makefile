# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stvalett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/31 11:29:38 by stvalett          #+#    #+#              #
#    Updated: 2017/04/06 18:07:49 by stvalett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L libft

LDLIBS = -lft

SRCS = src/built.c\
	   src/command.c\
	   src/env.c\
	   src/env2.c\
	   src/env_tools.c\
	   src/error.c\
	   src/execve.c\
	   src/main.c\
	   src/parse_built.c\
	   src/parse_built2.c\
	   src/parse_built3.c\
	   src/print.c\
	   src/signal.c\
	   src/tools.c\
	   src/tools_builts.c\
	   src/utils.c

OBJ = $(SRCS:.c=.o)

all : $(NAME)

OBJ : $(OBJ)
	@$(CC) $(CFLAGS) -c $(SRCS)

$(NAME) : $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)
	@sh progress_bar.sh
	@echo COMPIALTION MINISHELL OK !!!!

clean :
	@make clean -C libft
	@rm -rf $(OBJ)
	@sh progress_bar.sh
	@echo OBJ FROM MINISHELL REMOVE
	@sleep 2

fclean : clean
	@make fclean -C libft
	@rm -f $(NAME)
	@sh progress_bar.sh
	@echo BINAIRE MINISHELL REMOVE
	@sleep 2

re : fclean all
