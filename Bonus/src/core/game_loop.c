/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:04:03 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/22 16:03:02 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

void	game_fps(t_game *gunstorm)
{
	gunstorm->move_speed = 30.0 * gunstorm->mlx_data.mlx->delta_time;
	gunstorm->frames++;
	if (mlx_get_time() - gunstorm->start_time >= 1)
	{
		printf("FPS: %d\n", gunstorm->frames);
		gunstorm->frames = 0;
		gunstorm->start_time = mlx_get_time();
	}
}

int	rgba_color(t_rgb colors, int alpha, int y)
{
	float	brightness;
	float	distance_from_center;

	distance_from_center = fabsf((HEIGHT * 0.5f) - (float)y) / (HEIGHT * 0.5f);
	brightness = distance_from_center * 1.0;
	if (brightness < 0.2f)
		brightness = 0.2f;
	if (brightness > 1.0f)
		brightness = 1.0f;
	return (apply_brightness(colors, alpha, brightness));
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
				mlx_put_pixel(gunstorm->mlx_data.img, x, y,
					rgba_color(gunstorm->ceiling, 255, y));
			else
				mlx_put_pixel(gunstorm->mlx_data.img, x, y,
					rgba_color(gunstorm->floor, 255, y));
			y++;
		}
		x++;
	}
}

void	mouse_rotate_pov(t_game *gunstorm, float delta_time)
{
	static int		prev_x;
	static int		prev_y;
	static double	accum_dx;
	int				x;
	int				y;

	mlx_get_mouse_pos(gunstorm->mlx_data.mlx, &x, &y);
	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
	{
		mlx_set_mouse_pos(gunstorm->mlx_data.mlx, WIDTH / 2, HEIGHT / 2);
		prev_x = WIDTH / 2;
		prev_y = HEIGHT / 2;
		accum_dx = 0.0;
		return ;
	}
	accum_dx = accum_dx * 0.6 + (x - prev_x) * 0.00052 * delta_time * 20.0f;
	gunstorm->player.angle += accum_dx;
	prev_x = x;
	prev_y = y;
}

void	game_loop(void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	if (!gunstorm->start_game)
		return ;
	gunstorm->mlx_data.door_msg->enabled = false;
	menu(gunstorm);
	if (gunstorm->menu)
		return (display_menu(gunstorm));
	gun_up(gunstorm);
	update_player_anim(gunstorm, &gunstorm->player_anim);
	mlx_set_cursor_mode(gunstorm->mlx_data.mlx, MLX_MOUSE_HIDDEN);
	gunstorm->mlx_data.menu->enabled = false;
	gunstorm->mlx_data.circle->enabled = true;
	if (is_infront_door(gunstorm->map, gunstorm->player))
		gunstorm->mlx_data.door_msg->enabled = true;
	mouse_rotate_pov(gunstorm, gunstorm->mlx_data.mlx->delta_time);
	player_movement(gunstorm, &gunstorm->player);
	game_fps(gunstorm);
	clear_window(gunstorm);
	ray_cast(WIDTH, gunstorm, false);
	minimap(gunstorm);
}
