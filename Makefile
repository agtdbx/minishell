# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 14:20:53 by ngrenoux          #+#    #+#              #
#    Updated: 2022/12/07 13:47:54 by aderouba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS = --no-print-directory

#=================================COMPILATION==================================#
CC			= clang
FLAGS		= -Wall -Wextra -Werror -Iincludes -g3

#==================================EXECUTABLE==================================#
NAME		= minishell

#===================================INCLUDES===================================#
LIBFT		= libft

#=================================SOURCE FILES=================================#
SRCS		= srcs/main.c \
			  srcs/parsing/parsing.c \
			  srcs/parsing/parsing_utils.c \
			  srcs/parsing/command.c \
			  srcs/parsing/command_utils.c \
			  srcs/parsing/variable.c \
			  srcs/parsing/variable_utils.c \
			  srcs/parsing/variable_utils2.c \
			  srcs/parsing/env.c \
			  srcs/parsing/redirection.c \
			  srcs/parsing/redirection_utils.c \
			  srcs/parsing/redirection_utils2.c \
			  srcs/parsing/here_doc.c \
			  srcs/signal/signal.c \
			  srcs/execution/execution.c \
			  srcs/execution/execution_utils.c \
			  srcs/execution/builtins.c \
			  srcs/execution/exit.c \
			  srcs/execution/builtins_utils.c \
			  srcs/execution/export.c \
			  srcs/execution/export_utils.c \
			  srcs/execution/echo.c \
			  srcs/utils/init.c \


#====================================OBJECTS===================================#
OBJS		= $(SRCS:.c=.o)

#====================================COLORS====================================#
NOC			= \033[0m
BOLD		= \033[1m
UNDERLINE	= \033[4m
BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
VIOLET		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
NOC			= \033[0m

#====================================COUNTER===================================#
PERCENT = 0
NB_COMPILE = 0
TOTAL_COMPILE = $(words $(OBJS))

#=====================================RULES====================================#
all:
	@echo "$(BLUE)Compilation de minishell...$(NOC)"
	@echo "0%"
	@make $(NAME)

.c.o:
	$(eval NB_COMPILE=$(shell echo $$(($(NB_COMPILE)+1))))
	$(eval PERCENT=$(shell echo $$(($(NB_COMPILE) * 100 / $(TOTAL_COMPILE)))))
	@echo -e '\e[1A\e[K$(PERCENT)%'
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(OBJS)
	@echo "$(BLUE)Compilation de la libft...$(NOC)"
	@echo "0%"
	@make -sC $(LIBFT)
	@cp $(LIBFT)/libft.a ./libft.a
	@echo "$(BLUE)Création de l'executable...$(NOC)"
	@$(CC) -o $(NAME) $(OBJS) libft.a -lreadline
	@echo "$(GREEN)Tout est prêt !$(NOC)"

clean:
	@make -sC $(LIBFT) clean
	@rm -f $(OBJS)

fclean:	clean
	@make -sC $(LIBFT) fclean
	@rm -f $(NAME) libft.a

re:	fclean all
	@clear

.PHONY: all clean fclean re
