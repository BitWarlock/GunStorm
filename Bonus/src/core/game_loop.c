/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:04:03 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/09 17:00:14 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

void	game_fps(t_game *gunstorm)
{
	gunstorm->move_speed = gunstorm->mlx_data.mlx->delta_time * 40.0;
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

void	mouse_rotate_pov(t_game *gunstorm)
{
	static int			prev_x;
	static int			prev_y;
	static double		accum_dx;
	int					x;
	int					y;

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
	/*gunstorm->mlx_data.player->enabled = false;*/
	gunstorm->player_anim.frames[gunstorm->player_anim.current_frame]->enabled = false;
	gunstorm->mlx_data.circle->enabled = false;
	gunstorm->mlx_data.menu->enabled = true;
	mlx_set_cursor_mode(gunstorm->mlx_data.mlx, MLX_MOUSE_NORMAL);
}

void	menu(t_game *gunstorm)
{
	int	x;
	int	y;

	if (gunstorm->menu
		&& mlx_is_mouse_down(gunstorm->mlx_data.mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(gunstorm->mlx_data.mlx, &x, &y);
		if (x >= 600 && x <= 1400 && y >= 610 && y <= 730)
			gunstorm->menu = false;
		if (x >= 600 && x <= 1400 && y >= 770 && y <= 890)
			mlx_close_window(gunstorm->mlx_data.mlx);
	}
}



bool	infront_door(t_map map, t_pair player)
{
	int	x;
	int	y;

	x = floor(player.x / CELL_SIZE);
	y = floor(player.y / CELL_SIZE);
	if (x <= 0 || y <= 0
		|| y >= map.height - 1
		|| x >= (int)ft_strlen(map.rows[y]) - 1)
		return (false);
	if (map.rows[y - 1][x] == 'D'
		|| map.rows[y + 1][x] == 'D'
		|| map.rows[y][x - 1] == 'D'
		|| map.rows[y][x + 1] == 'D')
		return (true);
	else if (map.rows[y - 1][x] == 'O'
		|| map.rows[y + 1][x] == 'O'
		|| map.rows[y][x - 1] == 'O'
		|| map.rows[y][x + 1] == 'O')
		return (true);
	return (false);
}

void	gun_up(t_game *gunstorm)
{
	if (gunstorm->player_anim.current_frame == 0 && gunstorm->player_anim.frames[gunstorm->player_anim.current_frame]->instances[0].y > 280)
	{
		gunstorm->player_anim.frames[gunstorm->player_anim.current_frame]->instances[0].y -= 10;
	}
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
	if (infront_door(gunstorm->map, gunstorm->player.position))
		gunstorm->mlx_data.door_msg->enabled = true;
	mouse_rotate_pov(gunstorm);
	game_fps(gunstorm);
	clear_window(gunstorm);
	ray_cast(WIDTH, gunstorm, false);
	minimap(gunstorm);
}
