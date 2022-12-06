# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 14:20:53 by ngrenoux          #+#    #+#              #
#    Updated: 2022/12/05 18:29:43 by aderouba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
			  srcs/utils/init.c \
			  srcs/utils/utils.c


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

#=====================================RULES====================================#
all:	$(NAME)

.c.o:
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(OBJS)
	@make -j -sC $(LIBFT)
	@echo "$(BLUE)Compilation...$(NOC)"
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
