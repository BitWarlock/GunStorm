/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/16 23:07:20 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void	update_player_coord(t_player *player)
{
	player->position.x *= CELL_SIZE;
	player->position.y *= CELL_SIZE;
	player->position.x += (float)CELL_SIZE / 2;
	player->position.y += (float)CELL_SIZE / 2;
}

static void	game_init_vars(t_game *game, mlx_t *mlx)
{
	mlx_texture_t	*tex;
	mlx_image_t		*circle;
	mlx_image_t		*menu;

	(1 && (game->start_time = mlx_get_time()), (game->frames = 0));
	(1 && (game->start_game = false), (game->menu = false));
	game->player_anim.active = false;
	tex = mlx_load_png("./assets/circle.png");
	circle = mlx_texture_to_image(mlx, tex);
	mlx_resize_image(circle, 200, 200);
	mlx_delete_texture(tex);
	tex = mlx_load_png("./assets/menu.png");
	menu = mlx_texture_to_image(mlx, tex);
	mlx_image_to_window(mlx, circle, 1, 1);
	game->mlx_data.circle = circle;
	game->mlx_data.menu = menu;
	mlx_image_to_window(mlx, menu, 0, 0);
	game->player_anim.pos_x = WIDTH / 3;
	(1 && (game->player_anim.pos_y = 280), (menu->enabled = false));
	load_player_anim(game, &game->player_anim);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	game->mlx_data.door_msg = mlx_put_string(game->mlx_data.mlx,
			"Press O to open/close the door", WIDTH / 2, 300);
	game->mlx_data.door_msg->enabled = false;
	game->mlx_data.circle->enabled = false;
}

static void	game_init(t_game *gunstorm)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "GunStorm", true);
	if (!mlx)
		(free_all(gunstorm)), exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		(free_all(gunstorm)), mlx_terminate(mlx),
			exit(EXIT_FAILURE);
	gunstorm->mlx_data.mlx = mlx;
	gunstorm->mlx_data.img = img;
	game_init_vars(gunstorm, mlx);
}

static void	game_start(t_game *gunstorm)
{
	mlx_texture_t	*welcome_tex;
	mlx_image_t		*welcome_screen;

	game_init(gunstorm);
	welcome_tex = mlx_load_png("./assets/welcome.png");
	welcome_screen = mlx_texture_to_image(gunstorm->mlx_data.mlx, welcome_tex);
	mlx_image_to_window(gunstorm->mlx_data.mlx, welcome_screen, 0, 0);
	gunstorm->mlx_data.welcome_screen = welcome_screen;
	mlx_mouse_hook(gunstorm->mlx_data.mlx, player_attack, gunstorm);
	mlx_loop_hook(gunstorm->mlx_data.mlx, game_loop, gunstorm);
	mlx_key_hook(gunstorm->mlx_data.mlx, game_hooks, gunstorm);
	mlx_loop(gunstorm->mlx_data.mlx);
	mlx_terminate(gunstorm->mlx_data.mlx);
}

void	game_core(char *map_file)
{
	t_game	*gunstorm;

	gunstorm = malloc(sizeof(t_game));
	if (!gunstorm)
		fatal_error("malloc", strerror(errno));
	input_parsing(map_file, gunstorm);
	update_player_coord(&gunstorm->player);
	game_start(gunstorm);
	free_all(gunstorm);
}
