USER			:= $(shell whoami)
ERASE			= \033[2K\r
ORANGE			= \033[38;5;214m
TEAL			= \033[38;5;228m
RED				= \033[38;5;196m
GREEN			= \033[92m
NEON			= \033[38;5;51m
PURPLE			= \033[38;5;92;1m
RESET			= \033[0m
STRICT_FLAGS	= -Wall -Wextra -Werror -Wunused -Wconversion
DEBUG_FLAGS 	= -g3 -O0 -DDEBUG \
					-fno-inline -fno-omit-frame-pointer \
					-fstack-protector-all
FLAGS			= -O3 -g -Wshadow -Wnull-dereference
NAME			= cub3D
LIB_DIR			= ./libft
LIBFT			= $(LIB_DIR)/libft.a
MAIN_SOURCES 	= src/main.c

MAIN_OBJ 		= $(MAIN_SOURCES:.c=.o)

HEADER 			= include/gunstorm.h

CFLAGS			= $(FLAGS)

define PRINT_LOADING
	@printf "\n\033[2K\r$(GREEN)Compiling src/$*.c... $(RESET)\n"
	@for i in $(shell seq 0 100); do \
		printf "\033[2K\r$(BLUE)⟦$(RESET)"; \
		n=`expr $$i / 2 + 1`; \
		for j in `seq 1 $$n`; do printf "$(GREEN)▰$(RESET)"; done; \
		for j in `seq $$n 50`; do printf "▱"; done; \
		printf "$(BLUE)⟧$(RESET) $(GREEN)%3d%%$(RESET)" "$$i"; \
 		printf "$(RESET)"; \
	done; \
	printf "\n"
endef

define CLEAN_LOADING
	@for i in $(shell seq 0 100); do \
		printf "\033[2K\r$(BLUE)⟦$(RESET)"; \
		n=`expr $$i / 2 + 1`; \
		for j in `seq 1 $$n`; do printf "$(RED)▰$(RESET)"; done; \
		for j in `seq $$n 50`; do printf "▱"; done; \
		printf "$(BLUE)⟧$(RESET) $(RED)%3d%%$(RESET)" "$$i"; \
 		printf "$(RESET)"; \
		sleep 0.01; \
	done; \
	printf "\n"
endef

define MINISHELL_ART
\n\033[38;5;214;7m\033[0m\
\t\t\033[33;92;1m╔╦╗╦╔╗╔╦╔═╗╦ ╦╔═╗╦  ╦  \033[0m\n\
\t\t\033[33;92;1m║║║║║║║║╚═╗╠═╣║╣ ║  ║  \033[0m\n\
\t\t\033[33;92;1m╩ ╩╩╝╚╝╩╚═╝╩ ╩╚═╝╩═╝╩═╝\033[0m\n\
\033[0m
endef

CFLAGS_R += -L/Users/$(USER)/.brew/opt/readline/lib

	# @printf "%b\n" "$(value MINISHELL_ART)"
	# @echo "\t\t\t$(GREEN)IS READY$(RESET)"
all: $(NAME)
	@printf "\n"
	@printf "$(GREEN)██████╗  ██████╗ ███╗   ██╗███████╗██╗\n"
	@printf "██╔══██╗██╔═══██╗████╗  ██║██╔════╝██║\n"
	@printf "██║  ██║██║   ██║██╔██╗ ██║█████╗  ██║\n"
	@printf "██║  ██║██║   ██║██║╚██╗██║██╔══╝  ╚═╝\n"
	@printf "██████╔╝╚██████╔╝██║ ╚████║███████╗██╗\n"
	@printf "╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚═╝$(RESET)\n"
	@printf "\n$(TEAL)$(BOLD)$(NAME) is ready!$(RESET)\n\n"

libft: $(LIBFT)

src/%.o: src/%.c $(HEADER) Makefile
	$(PRINT_LOADING)
	@cc -c $< -o $@ $(CFLAGS)

$(NAME): $(MAIN_OBJ) $(LIBFT)
	@cc $^ -o $@ $(CFLAGS)

$(LIBFT):
	@$(MAKE) -sC $(LIB_DIR)

clean:
	@echo "$(RED)Cleaning up $(NAME)...$(RESET)"
	$(CLEAN_LOADING)
	@$(RM) $(MAIN_OBJ)
	@$(MAKE) -sC libft/ clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -sC libft/ fclean

re: fclean all


.PHONY: check
