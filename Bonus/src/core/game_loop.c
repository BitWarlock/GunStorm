/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:04:03 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/27 15:21:20 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

void	game_fps(t_game *gunstorm)
{
	float	fps;

	fps = 1.0 / gunstorm->mlx_data.mlx->delta_time;
	gunstorm->move_speed = gunstorm->mlx_data.mlx->delta_time * 20.0;
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

void	game_loop(void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	mouse_rotate_pov(gunstorm);
	game_fps(gunstorm);
	clear_window(gunstorm);
	ray_cast(WIDTH, gunstorm, false);
	minimap(gunstorm);
}
