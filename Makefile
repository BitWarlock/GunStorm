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
CFLAGS			= -Ofast -Wall -Wextra -Werror
MLXFLAGS		= -lm -lpthread -lglfw
NAME			= cub3D
NAME2			= cub3D_BONUS
LIB_DIR			= ./libft
LIBFT			= $(LIB_DIR)/libft.a

SOURCES		 	= src/parser/validate_colors.c src/parser/validate_identifiers.c \
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

B_SOURCES 		= src/parser/validate_colors_bonus.c src/parser/validate_identifiers_bonus.c \
				  src/parser/validate_map_bonus.c src/parser/validate_map_walls_bonus.c \
				  src/parser/validate_textures_bonus.c src/parser/input_parsing_bonus.c \
				  src/parser/flood_fill_bonus.c \
				  \
				  src/utils/char_utils_bonus.c src/utils/color_utils_bonus.c src/utils/string_utils_bonus.c \
				  src/utils/error_handling_bonus.c src/utils/memory_free_bonus.c \
				  \
				  src/core/game_core_bonus.c src/core/game_loop_bonus.c src/core/game_hooks_bonus.c src/core/main_bonus.c \
				  \
				  src/render/ray_cast_bonus.c src/render/ray_cast_dda_bonus.c src/render/ray_render_bonus.c \
				  src/render/minimap_bonus.c \
				  src/render/draw_triangle_bonus.c src/render/player_animation_bonus.c \
				  src/render/menu_and_door_bonus.c src/core/player_movement_bonus.c \
				  src/core/game_init_bonus.c src/render/render_sky_floor_bonus.c

SOUND_SOURCES	= Bonus/src/core/game_sound_bonus.c

MAIN_SOURCES	= $(addprefix Simple/, $(SOURCES))

BONUS_SOURCES	= $(addprefix Bonus/, $(B_SOURCES))

OBJS_DIR		= objs

B_OBJS_DIR		= b_objs

MAIN_OBJ 		= $(addprefix $(OBJS_DIR)/, $(MAIN_SOURCES:.c=.o))

BONUS_OBJ 		= $(addprefix $(B_OBJS_DIR)/, $(BONUS_SOURCES:.c=.o))

SOUND_OBJ 		= $(addprefix $(OBJS_DIR)/, $(SOUND_SOURCES:.c=.o))

HEADER 			= Simple/include/gunstorm.h

B_HEADER		= Bonus/include/gunstorm_bonus.h Bonus/include/miniaudio_types_bonus.h Sound/miniaudio.h

FLAGS			= $(CFLAGS)

define PRINT_LOADING
	@printf "\n\033[2K\r$(GREEN)Compiling $*... $(RESET)\n"
	@# Determine the sleep duration based on the file name
	@if echo "$*" | grep -q "src/core/game_sound"; then \
		sleep_duration=0.7; \
	else \
		sleep_duration=0.001; \
	fi; \
	for i in $(shell seq 0 100); do \
		if [ $$((i % 5)) -eq 0 ]; then \
			printf "\033[2K\r$(BLUE)⟦$(RESET)"; \
			n=`expr $$i / 2 + 1`; \
			for j in `seq 1 $$n`; do printf "$(GREEN)▰$(RESET)"; done; \
			for j in `seq $$n 50`; do printf "▱"; done; \
			printf "$(BLUE)⟧$(RESET) $(GREEN)%3d%%$(RESET)" "$$i"; \
			printf "$(RESET)"; \
		fi; \
		sleep $$sleep_duration; \
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
	@cc $^ MLX42/build/libmlx42.a $(MLXFLAGS) -o $@ $(CFLAGS)

$(B_OBJS_DIR)/Bonus/src/core/game_sound_bonus.o: $(SOUND_SOURCES)
	@mkdir -p $(dir $@)
	$(PRINT_LOADING)
	@cc -c $< -o $@ $(CFLAGS)

$(B_OBJS_DIR)/%.o: %.c $(B_HEADER) Makefile
	@mkdir -p $(dir $@)
	$(PRINT_LOADING)
	@cc -c $< -o $@ $(CFLAGS)

$(NAME2): $(BONUS_OBJ) $(SOUND_OBJ) $(LIBFT)
	@cc $^ MLX42/build/libmlx42.a $(MLXFLAGS) -o $@ $(CFLAGS)

bonus: $(NAME2)
	@printf "\n$(GREEN)"
	@printf "██████╗  ██████╗ ███╗   ██╗███████╗██╗\n"
	@printf "██╔══██╗██╔═══██╗████╗  ██║██╔════╝██║\n"
	@printf "██║  ██║██║   ██║██╔██╗ ██║█████╗  ██║\n"
	@printf "██║  ██║██║   ██║██║╚██╗██║██╔══╝  ╚═╝\n"
	@printf "██████╔╝╚██████╔╝██║ ╚████║███████╗██╗\n"
	@printf "╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚═╝$(RESET)\n"
	@printf "\n$(TEAL)$(BOLD)$(NAME2) is ready!$(RESET)\n\n"

$(LIBFT):
	$(PRINT_LOADING)
	@$(MAKE) -sC $(LIB_DIR)

clean:
	@echo "$(RED)Cleaning up $(NAME)...$(RESET)"
	$(CLEAN_LOADING)
	@$(RM) -rf $(MAIN_OBJ) $(OBJS_DIR) $(B_OBJS_DIR)
	@$(MAKE) -sC libft/ clean

fclean: clean
	@$(RM) $(NAME) $(NAME2)
	@$(MAKE) -sC libft/ fclean

re: fclean all

.PHONY: clean
