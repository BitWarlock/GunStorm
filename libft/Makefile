# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 05:47:36 by mrezki            #+#    #+#              #
#    Updated: 2024/02/17 14:27:37 by mrezki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
RM		= rm -rf
CFLAGS		= -Wall -Wextra -Werror

SRCS		= ft_isalpha.c ft_isdigit.c ft_isalnum.c \
		ft_isascii.c ft_isprint.c ft_strlen.c \
		ft_toupper.c ft_tolower.c ft_memcpy.c \
		ft_memset.c ft_bzero.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memcmp.c \
		ft_memchr.c ft_strnstr.c ft_atoi.c \
		ft_calloc.c ft_strdup.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c \
		ft_split.c ft_strmapi.c ft_striteri.c \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_printf.c \
		utils.c print_char.c print_int.c print_hex.c get_next_line_bonus.c \
		get_next_line_utils_bonus.c ft_fd_printf.c\


OBJS		= $(SRCS:.c=.o)


all: $(NAME)

%.o: %.c libft.h
	@$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJS)
	@$(AR) rcs $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME) a.out .DS_Store

re: fclean all

.PHONY: clean
