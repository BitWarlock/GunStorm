USER			:= $(shell whoami)
ERASE			= \033[2K\r
ORANGE			= \033[38;5;214m
TEAL			= \033[38;5;228m
RED				= \033[38;5;196m
GREEN			= \033[92m
NEON			= \033[38;5;51m
PURPLE			= \033[38;5;92;1m
BOLD			= \033[1m
RESET			= \033[0m
STRICT_FLAGS	= -Wall -Wextra -Werror -Wunused -Wconversion
DEBUG_FLAGS 	= -g3 -O0 -DDEBUG \
					-fno-inline -fno-omit-frame-pointer \
					-fstack-protector-all
FLAGS			= -O3 -g -Wshadow -Wnull-dereference #-fsanitize=address
NAME			= cub3D
LIB_DIR			= ./libft
LIBFT			= $(LIB_DIR)/libft.a
MAIN_SOURCES 	= src/parser/validate_colors.c src/parser/validate_identifiers.c \
				  src/parser/validate_map.c src/parser/validate_map_walls.c \
				  src/parser/validate_textures.c src/parser/input_parsing.c \
				  src/parser/flood_fill.c \
				  \
				  src/utils/char_utils.c src/utils/color_utils.c src/utils/string_utils.c \
				  src/utils/error_handling.c src/utils/memory_free.c \
				  \
				  src/core/game_core.c src/core/game_loop.c src/core/hooks.c src/core/main.c \
				  \
				  src/render/ray_cast.c src/render/ray_cast_dda.c src/render/ray_render.c \
				  src/render/2dmap.c

OBJS_DIR		= objs

MAIN_OBJ 		= $(addprefix $(OBJS_DIR)/, $(MAIN_SOURCES:.c=.o))

HEADER 			= include/gunstorm.h

CFLAGS			= $(FLAGS)

define PRINT_LOADING
	@printf "\n\033[2K\r$(GREEN)Compiling $*... $(RESET)\n"
	@for i in $(shell seq 0 100); do \
		if [ $$((i % 5)) -eq 0 ]; then \
			printf "\033[2K\r$(BLUE)⟦$(RESET)"; \
			n=`expr $$i / 2 + 1`; \
			for j in `seq 1 $$n`; do printf "$(GREEN)▰$(RESET)"; done; \
			for j in `seq $$n 50`; do printf "▱"; done; \
			printf "$(BLUE)⟧$(RESET) $(GREEN)%3d%%$(RESET)" "$$i"; \
			printf "$(RESET)"; \
		fi; \
		sleep 0.002; \
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

CFLAGS_R += -L/Users/$(USER)/.brew/opt/readline/lib

all: $(NAME)
	@printf "\n$(GREEN)"
	@printf "██████╗  ██████╗ ███╗   ██╗███████╗██╗\n"
	@printf "██╔══██╗██╔═══██╗████╗  ██║██╔════╝██║\n"
	@printf "██║  ██║██║   ██║██╔██╗ ██║█████╗  ██║\n"
	@printf "██║  ██║██║   ██║██║╚██╗██║██╔══╝  ╚═╝\n"
	@printf "██████╔╝╚██████╔╝██║ ╚████║███████╗██╗\n"
	@printf "╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚═╝$(RESET)\n"
	@printf "\n$(TEAL)$(BOLD)$(NAME) is ready!$(RESET)\n\n"

libft: $(LIBFT)

$(OBJS_DIR)/%.o: %.c $(HEADER) Makefile
	@mkdir -p $(dir $@)
	$(PRINT_LOADING)
	@cc -c $< -o $@ $(CFLAGS)

$(NAME): $(MAIN_OBJ) $(LIBFT)
	@cc $^ ../MLX42/build/libmlx42.a -lglfw -lm -o $@ $(CFLAGS)

$(LIBFT):
	$(PRINT_LOADING)
	@$(MAKE) -sC $(LIB_DIR)

clean:
	@echo "$(RED)Cleaning up $(NAME)...$(RESET)"
	$(CLEAN_LOADING)
	@$(RM) -rf $(MAIN_OBJ) $(OBJS_DIR)
	@$(MAKE) -sC libft/ clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -sC libft/ fclean

re: fclean all

.PHONY: clean
