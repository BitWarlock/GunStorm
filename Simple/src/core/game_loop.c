/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:04:03 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/14 23:27:42 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

void	game_fps(t_game *gunstorm)
{
	float	fps;

	fps = 1.0 / gunstorm->mlx_data.mlx->delta_time;
	gunstorm->move_speed = gunstorm->mlx_data.mlx->delta_time * 80.0;
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

void	game_loop(void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	game_fps(gunstorm);
	clear_window(gunstorm);
	ray_cast(WIDTH, gunstorm, false);
}
