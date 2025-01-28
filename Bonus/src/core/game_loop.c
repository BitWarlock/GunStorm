/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:04:03 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/28 16:46:20 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

void	game_fps(t_game *gunstorm)
{
	gunstorm->move_speed = gunstorm->mlx_data.mlx->delta_time * 30.0;
	gunstorm->frames++;
	if (mlx_get_time() - gunstorm->start_time >= 1)
	{
		printf("FPS: %d\n", gunstorm->frames);
		gunstorm->frames = 0;
		gunstorm->start_time = mlx_get_time();
	}
}

static int	rgba_color(t_rgb colors, int alpha)
{
	return (colors.r << 24
		| colors.g << 16 | colors.b << 8
		| alpha);
}

static void	clear_window(t_game *gunstorm)
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

void    mouse_rotate_pov(t_game *gunstorm)
{
	static int        prev_x;
	static int        prev_y;
	static double    accum_dx;
	int                x;
	int                y;

	mlx_get_mouse_pos(gunstorm->mlx_data.mlx, &x, &y);
	if (x <= 0 || x >= WIDTH
		|| y <= 0 || y >= HEIGHT)
	{
		mlx_set_mouse_pos(gunstorm->mlx_data.mlx, WIDTH / 2, HEIGHT / 2);
		prev_x = WIDTH / 2;
		prev_y = HEIGHT / 2;
		accum_dx = 0.0;
		return ;
	}
	accum_dx = accum_dx * 0.6 + (x - prev_x) * 0.0004;
	gunstorm->player.angle += accum_dx;
	prev_x = x;
	prev_y = y;
}

void	display_menu(t_game *gunstorm)
{
	gunstorm->mlx_data.circle->enabled = false;
	gunstorm->mlx_data.menu->enabled = true;
}

void	game_loop(void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	if (gunstorm->menu &&
		mlx_is_mouse_down(gunstorm->mlx_data.mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		int x, y;
		mlx_get_mouse_pos(gunstorm->mlx_data.mlx, &x, &y);
		if (x >= 702 && x <= 1245 && y >= 687 && y <= 745)  // Resume
		{
			gunstorm->menu = false;
			mlx_set_cursor_mode(gunstorm->mlx_data.mlx, MLX_MOUSE_HIDDEN);
		}
		if (x >= 779 && x <= 1197 && y >= 815 && y <= 869)  // Quit
			mlx_close_window(gunstorm->mlx_data.mlx);
	}
	if (gunstorm->menu)
		return (display_menu(gunstorm));
	gunstorm->mlx_data.menu->enabled = false;
	gunstorm->mlx_data.circle->enabled = true;
	mouse_rotate_pov(gunstorm);
	game_fps(gunstorm);
	clear_window(gunstorm);
	ray_cast(WIDTH, gunstorm, false);
	minimap(gunstorm);
}
