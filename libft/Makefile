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
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
OBJS_DIR	= objs
RED			= \033[38;5;196m
TEAL		= \033[38;5;228m
GREEN		= \033[92m
RESET		= \033[0m
CYAN    	= \033[36m
MAGENTA 	= \033[35m

SRCS		= character_utils/ft_isalnum.c character_utils/ft_isalpha.c \
			  character_utils/ft_isascii.c character_utils/ft_isdigit.c \
			  character_utils/ft_isprint.c character_utils/ft_tolower.c \
			  character_utils/ft_toupper.c \
			  \
			  linked_list/ft_lstadd_back_bonus.c linked_list/ft_lstadd_front_bonus.c \
			  linked_list/ft_lstclear_bonus.c linked_list/ft_lstdelone_bonus.c \
			  linked_list/ft_lstiter_bonus.c linked_list/ft_lstlast_bonus.c \
			  linked_list/ft_lstmap_bonus.c linked_list/ft_lstnew_bonus.c \
			  linked_list/ft_lstsize_bonus.c \
			  \
			  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
			  \
			  memory/ft_bzero.c memory/ft_calloc.c memory/ft_memchr.c \
			  memory/ft_memcmp.c memory/ft_memcpy.c memory/ft_memmove.c \
			  memory/ft_memset.c \
			  \
			  printf/ft_fd_printf.c printf/ft_printf.c printf/ft_putchar_fd.c \
			  printf/ft_putendl_fd.c printf/ft_putnbr_fd.c printf/ft_putstr_fd.c \
			  printf/print_char.c printf/printf_utils.c printf/print_hex.c printf/print_int.c \
			  \
			  strings/ft_atoi.c strings/ft_itoa.c strings/ft_split.c strings/ft_strchr.c \
			  strings/ft_strdup.c strings/ft_striteri.c strings/ft_strjoin.c \
			  strings/ft_strlcat.c strings/ft_strlcpy.c strings/ft_strlen.c \
			  strings/ft_strmapi.c strings/ft_strncmp.c strings/ft_strnstr.c \
			  strings/ft_strrchr.c strings/ft_strtrim.c strings/ft_substr.c

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(OBJS_DIR)/%.o: %.c libft.h
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJS)
	@$(AR) rcs $(NAME) $(OBJS)

define CLEAN_LOADING
	@for i in $(shell seq 0 10); do \
		printf "\033[2K\r$(RESET)"; \
		case `expr $$i % 6` in \
			0) printf "$(RED)○○○●○○";; \
			1) printf "$(RED)○○●○○○";; \
			2) printf "$(RED)○●○○○○";; \
			3) printf "$(RED)●○○○○○";; \
			4) printf "$(RED)○○○○○●";; \
			5) printf "$(RED)○○○○●○";; \
		esac; \
		sleep 0.008; \
	done; \
	printf "\n$(RESET)"
endef

clean:
	@echo "$(RED)Cleaning up libft...$(RESET)"
	$(CLEAN_LOADING)
	@$(RM) $(OBJS) $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME) a.out .DS_Store

re: fclean all

.PHONY: clean
