/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/19 18:02:03 by mrezki           ###   ########.fr       */
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

static void	game_init_vars(t_game *gunstorm, mlx_t *mlx)
{
	mlx_texture_t	*tex;
	mlx_image_t		*circle;
	mlx_image_t		*menu;

	gunstorm->start_time = mlx_get_time();
	gunstorm->frames = 0;
	gunstorm->start_game = false;
	gunstorm->menu = false;
	gunstorm->movement.forward = false;
	gunstorm->movement.backward = false;
	gunstorm->movement.right = false;
	gunstorm->movement.left = false;
	tex = mlx_load_png("./assets/circle2.png");
	circle = mlx_texture_to_image(mlx, tex);
	mlx_resize_image(circle, 200, 200);
	mlx_delete_texture(tex);
	tex = mlx_load_png("./assets/menu.png");
	menu = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	mlx_image_to_window(mlx, circle, 1, 1);
	gunstorm->mlx_data.circle = circle;
	gunstorm->mlx_data.menu = menu;
	mlx_image_to_window(mlx, menu, 0, 0);
	menu->enabled = false;
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	gunstorm->mlx_data.door_msg = mlx_put_string(gunstorm->mlx_data.mlx,
			"Press E to open/close the door", WIDTH / 2, 300);
	gunstorm->mlx_data.door_msg->enabled = false;
	gunstorm->mlx_data.circle->enabled = false;
	gunstorm->player_anim.pos_x = WIDTH / 3;
	gunstorm->player_anim.pos_y = 280;
	load_player_anim(gunstorm, &gunstorm->player_anim);
}

void	game_init_sound(t_gunsound *sound_system)
{
	if (ma_engine_init(NULL, &sound_system->engine) != MA_SUCCESS)
	{
		printf("Failed to initialize audio engine.\n");
		return ;
	}
	if (ma_sound_init_from_file(&sound_system->engine, "../Sound/gunshot.mp3",
			0, NULL, NULL, &sound_system->gunshot) != MA_SUCCESS)
	{
		printf("Failed to load gunshot sound.\n");
		ma_engine_uninit(&sound_system->engine);
		return ;
	}
	sound_system->sound_loaded = true;
}

static void	game_init_mlx(t_game *gunstorm)
{
	int			width;
	int			height;
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "GunStorm", true);
	if (!mlx)
		(free_all(gunstorm)), exit(EXIT_FAILURE);
	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_pos(mlx, (width - WIDTH) / 2, (height - HEIGHT) / 2);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		(free_all(gunstorm)), mlx_terminate(mlx), exit(EXIT_FAILURE);
	gunstorm->mlx_data.mlx = mlx;
	gunstorm->mlx_data.img = img;
}

static void	game_init(t_game *gunstorm)
{
	game_init_mlx(gunstorm);
	game_init_vars(gunstorm, gunstorm->mlx_data.mlx);
	game_init_sound(&gunstorm->sound_system);
}

static void	game_start(t_game *gunstorm)
{
	mlx_texture_t	*welcome_tex;
	mlx_image_t		*welcome_screen;

	game_init(gunstorm);
	welcome_tex = mlx_load_png("./assets/welcome.png");
	welcome_screen = mlx_texture_to_image(gunstorm->mlx_data.mlx, welcome_tex);
	mlx_delete_texture(welcome_tex);
	mlx_image_to_window(gunstorm->mlx_data.mlx, welcome_screen, 0, 0);
	mlx_mouse_hook(gunstorm->mlx_data.mlx, player_attack, gunstorm);
	gunstorm->mlx_data.welcome_screen = welcome_screen;
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
	game_sound_init(gunstorm, &gunstorm->sound);
	game_start(gunstorm);
	free_sound(gunstorm);
	free_all(gunstorm);
}
