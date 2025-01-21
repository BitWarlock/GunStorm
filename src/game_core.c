/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/21 21:41:29 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gunstorm.h"

void	update_player_coord(t_player *player)
{
	player->position.x *= CELL_SIZE;
	player->position.y *= CELL_SIZE;
	player->position.x += (float)CELL_SIZE / 2;
	player->position.y += (float)CELL_SIZE / 2;
}

void	game_init(t_game *gunstorm)
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
	gunstorm->start_time = mlx_get_time();
	gunstorm->frames = 0;
}

int	rgba_color(t_rgb colors, int alpha)
{
	return (colors.r << 24
		| colors.g << 16 | colors.b << 8
		| alpha);
}

void	clear_window(t_game *gunstorm)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y <= HEIGHT / 2)
				mlx_put_pixel(gunstorm->mlx_data.img,
					x, y, rgba_color(gunstorm->ceiling, 150));
			else
				mlx_put_pixel(gunstorm->mlx_data.img,
					x, y, rgba_color(gunstorm->floor, 50));
			y++;
		}
		x++;
	}
}

void	mouse_hook(t_game *gunstorm)
{
	static int	prev_x = WIDTH / 2;  // Save previous mouse X position
	static int	prev_y = HEIGHT / 2; // Save previous mouse Y position
	int			x;
	int			y;

	// Get the current mouse position
	mlx_get_mouse_pos(gunstorm->mlx_data.mlx, &x, &y);

	// Recenter the mouse when it reaches the edges
	if (x <= 0 || x >= WIDTH - 1 || y <= 0 || y >= HEIGHT - 1)
	{
		mlx_set_mouse_pos(gunstorm->mlx_data.mlx, WIDTH / 2, HEIGHT / 2);
		prev_x = WIDTH / 2;
		prev_y = HEIGHT / 2;
		return;
	}

	// Adjust the player's angle based on mouse movement
	if (x < prev_x)
		gunstorm->player.angle -= 0.04 - 0.001;
	else if (x > prev_x)
		gunstorm->player.angle += 0.04 - 0.001;

	// Update previous mouse position
	prev_x = x;
	prev_y = y;
}

void	game_loop(void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	game_fps(gunstorm);
	clear_window(gunstorm);
	mouse_hook(gunstorm);
	raycaster(WIDTH, gunstorm, false);
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	if (ydelta < 0)
		gunstorm->player.angle -= 0.1;
	if (ydelta > 0)
		gunstorm->player.angle += 0.1;
}

void	game_start(t_game *gunstorm)
{
	mlx_loop_hook(gunstorm->mlx_data.mlx, game_loop, gunstorm);
	mlx_key_hook(gunstorm->mlx_data.mlx, game_hooks, gunstorm);
	mlx_scroll_hook(gunstorm->mlx_data.mlx, scroll_hook, gunstorm);
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
	game_init(gunstorm);
	game_start(gunstorm);
	/*map_2d(gunstorm);*/
	free_all(gunstorm);
}
