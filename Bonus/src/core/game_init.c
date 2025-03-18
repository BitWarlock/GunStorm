/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:01:16 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/17 23:23:50 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void	game_init_vars(t_game *gunstorm)
{
	gunstorm->ray_angle_step = FOV / (float)WIDTH;
	gunstorm->player.angle_degree = (int)
		(gunstorm->player.angle * 1800.0 / M_PI) % 3600;
	gunstorm->game_has_doors = map_has_doors(gunstorm->map);
	gunstorm->mlx_data.door_msg->enabled = false;
	gunstorm->mlx_data.circle->enabled = false;
	gunstorm->mlx_data.menu->enabled = false;
	gunstorm->player_anim.pos_x = WIDTH / 3;
	gunstorm->start_time = mlx_get_time();
	gunstorm->movement.backward = false;
	gunstorm->movement.forward = false;
	gunstorm->player_anim.pos_y = 0;
	gunstorm->movement.right = false;
	gunstorm->movement.left = false;
	gunstorm->start_game = false;
	gunstorm->menu = false;
	gunstorm->frames = 0;
}

static mlx_image_t	*init_texture(char *path, mlx_t *mlx, t_game *gunstorm)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		(free_all(gunstorm)),
			fatal_error("Asset failed to load", NULL);
	img = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (img);
}

static void	game_init_mlx_assets(t_game *gunstorm, mlx_t *mlx)
{
	mlx_image_t		*welcome_screen;
	mlx_texture_t	*tex;
	mlx_image_t		*circle;
	mlx_image_t		*menu;

	welcome_screen = init_texture("./assets/welcome.png", mlx, gunstorm);
	circle = init_texture("./assets/circle2.png", mlx, gunstorm);
	mlx_resize_image(circle, 200, 200);
	menu = init_texture("./assets/menu.png", mlx, gunstorm);
	mlx_image_to_window(mlx, circle, 1, 1);
	mlx_image_to_window(mlx, menu, 0, 0);
	mlx_image_to_window(mlx, welcome_screen, 0, 0);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	gunstorm->mlx_data.door_msg = mlx_put_string(gunstorm->mlx_data.mlx,
			"Press E to open/close the door", WIDTH / 2, 300);
	gunstorm->mlx_data.menu = menu;
	gunstorm->mlx_data.circle = circle;
	gunstorm->mlx_data.welcome_screen = welcome_screen;
}

static void	game_init_mlx(t_game *gunstorm)
{
	int			width;
	int			height;
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "GunStorm", true);
	if (!mlx)
		(free_all(gunstorm)), fatal_error("MLX library failed", NULL);
	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_pos(mlx, (width - WIDTH) / 2, (height - HEIGHT) / 2);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		(free_all(gunstorm)), mlx_terminate(mlx),
			fatal_error("MLX library failed", NULL);
	gunstorm->mlx_data.mlx = mlx;
	gunstorm->mlx_data.img = img;
}

void	game_init(t_game *gunstorm)
{
	game_init_mlx(gunstorm);
	game_init_mlx_assets(gunstorm, gunstorm->mlx_data.mlx);
	game_init_vars(gunstorm);
	game_init_animations(gunstorm, &gunstorm->player_anim);
	game_init_soundtrack(gunstorm, &gunstorm->sound);
	game_init_gunsound(&gunstorm->sound_system, gunstorm);
	game_init_lookup_t(gunstorm);
}
