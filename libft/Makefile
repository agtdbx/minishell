# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 12:24:51 by aderouba          #+#    #+#              #
#    Updated: 2022/12/08 10:35:14 by aderouba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS = --no-print-directory

#=================================COMPILATION==================================#
CC = clang
CFLAGS = -g -Wall -Wextra -Werror

#==================================EXECUTABLE==================================#
NAME = libft.a

#===================================INCLUDES===================================#
INCLUDE = -I .

#=================================SOURCE FILES=================================#
SRCS =	ft_atof.c \
		ft_atoi_base.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_ftoa.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprime.c \
		ft_isprint.c \
		ft_itoa_base.c \
		ft_itoa.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstr.c \
		ft_lstsize.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_pow.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_base_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_putunbr_base_fd.c \
		ft_putunbr_fd.c \
		ft_split.c \
		ft_sqrt.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin_free_1st_p.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strstr.c \
		ft_strsuperjoin_free_1st_p.c \
		ft_strsuperjoin.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_supersplit.c \
		ft_tolower.c \
		ft_toupper.c \
		gnl.c \
		printf_fd.c \
		printf.c

#====================================OBJECTS===================================#
OBJS = ${SRCS:.c=.o}

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

NORMAL		= \e[25
BLINK		= \e[5m

#==============================PROGRESS BAR UTILS==============================#
PERCENT = 0
NB_COMPIL = 0
TOTAL_COMPIL = $(words $(OBJS))
PROGRESS_BAR_DETAIL = 5

#=====================================RULES====================================#
all : $(NAME)

%.o : %.c
	$(if $(filter $(NB_COMPIL),0), @echo "$(YELLOW)$(NB_COMPIL) 0%$(NOC)")
	$(if $(filter $(NB_COMPIL),0), @make create_progressbar)
	$(eval NB_COMPIL=$(shell echo $$(($(NB_COMPIL)+1))))
	$(eval PERCENT=$(shell echo $$(($(NB_COMPIL) * 100 / $(TOTAL_COMPIL)))))
	@echo -ne '\e[1A\e[K'
	@./.progressbar $(PERCENT)
	$(if $(filter $(PERCENT),100), @echo "$(GREEN)$(PERCENT)%$(NOC)", @echo "$(YELLOW)$(PERCENT)%$(NOC)")
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME) : $(OBJS)
	@rm .progressbar
	@ar cr $@ $^

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean $(NAME)

create_progressbar:
	@echo '#!/bin/bash\n' > .progressbar
	@echo "NOC='\033[0m'" >> .progressbar
	@echo "RED='\033[1;31m'" >> .progressbar
	@echo "GREEN='\033[1;32m'\n" >> .progressbar
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
