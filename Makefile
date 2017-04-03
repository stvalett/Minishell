# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stvalett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/31 11:29:38 by stvalett          #+#    #+#              #
#    Updated: 2017/03/31 17:04:28 by stvalett         ###   ########.fr        #
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
	$(CC) $(CFLAGS) -c $(SRCS)

$(NAME) : $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)
	@echo COMPIALTION FT_MINISHELL OK !!!!

clean :
	@make clean -C libft
	@rm -rf $(OBJ)
	@echo REMOVE OBJ

fclean : clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo REMOVE BINAIRE

re : fclean all
