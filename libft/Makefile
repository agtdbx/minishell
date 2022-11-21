# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderouba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 12:24:51 by aderouba          #+#    #+#              #
#    Updated: 2022/11/21 17:22:29 by aderouba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_atof.c \
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

OBJ = ${SRC:.c=.o}

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
INCLUDE = -I .

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME) : $(OBJ)
	@ar cr $@ $^

all : $(NAME)

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean $(NAME)

.PHONY: all clean fclean re
