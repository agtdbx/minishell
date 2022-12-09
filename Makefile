# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 14:20:53 by ngrenoux          #+#    #+#              #
#    Updated: 2022/12/09 17:47:13 by aderouba         ###   ########.fr        #
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
			  srcs/parsing/here_doc_utils.c \
			  srcs/parsing/quote.c \
			  srcs/signal/signal.c \
			  srcs/execution/execution.c \
			  srcs/execution/execution_utils.c \
			  srcs/execution/execution_utils2.c \
			  srcs/execution/builtins.c \
			  srcs/execution/exit.c \
			  srcs/execution/builtins_utils.c \
			  srcs/execution/export.c \
			  srcs/execution/export_utils.c \
			  srcs/execution/echo.c \
			  srcs/utils/init.c \
			  srcs/utils/error.c \


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

#==============================PROGRESS BAR UTILS==============================#
PERCENT = 0
NB_COMPIL = 0
TOTAL_COMPIL = $(words $(OBJS))
PROGRESS_BAR_DETAIL = 5

#=====================================RULES====================================#
all: $(NAME)

.c.o:
	$(if $(filter $(NB_COMPIL),0), @echo "$(BLUE)Compilation de minishell...$(NOC)")
	$(if $(filter $(NB_COMPIL),0), @echo "$(YELLOW)$(NB_COMPIL) 0%$(NOC)")
	$(if $(filter $(NB_COMPIL),0), @make create_progressbar)
	$(eval NB_COMPIL=$(shell echo $$(($(NB_COMPIL)+1))))
	$(eval PERCENT=$(shell echo $$(($(NB_COMPIL) * 100 / $(TOTAL_COMPIL)))))
	@echo -ne '\e[1A\e[K'
	@./.progressbar $(PERCENT)
	$(if $(filter $(PERCENT),100), @echo "$(GREEN)$(PERCENT)%$(NOC)", @echo "$(YELLOW)$(PERCENT)%$(NOC)")
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo -ne '\e[1A\e[K'
	@./.progressbar 100
	@echo "$(GREEN)100%$(NOC)"
	@rm .progressbar
	@echo "$(BLUE)Compilation de la libft...$(NOC)"
	@make -sC $(LIBFT)
	@cp $(LIBFT)/libft.a ./libft.a
	@echo "$(BLUE)Création de l'executable...$(NOC)"
	@$(CC) -o $(NAME) $(OBJS) libft.a -lreadline
	@echo "$(GREEN)Tout est prêt !$(NOC)"

clean:
	@echo "$(RED)Suppression des objets$(NOC)"
	@make -sC $(LIBFT) clean
	@rm -f $(OBJS)

fclean:	clean
	@echo "$(RED)Suppression des binaires$(NOC)"
	@make -sC $(LIBFT) fclean
	@rm -f $(NAME) libft.a

re:
	@clear
	@make fclean
	@make all

create_progressbar:
	@echo '#!/bin/bash\n' > .progressbar
	@echo 'for i in {0..100..$(PROGRESS_BAR_DETAIL)}' >> .progressbar
	@echo 'do' >> .progressbar
	@echo '	if [ $$i -gt $$1 ]' >> .progressbar
	@echo '	then' >> .progressbar
	@echo '		echo -ne "$(RED)█$(NOC)"' >> .progressbar
	@echo '	else' >> .progressbar
	@echo '		echo -ne "$(GREEN)█$(NOC)"' >> .progressbar
	@echo '	fi' >> .progressbar
	@echo 'done' >> .progressbar
	@echo 'echo -n " "' >> .progressbar
	@chmod 777 .progressbar

.PHONY: all clean fclean re create_progressbar
