/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:42:54 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/16 03:07:19 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

void	move_in_playerdir(mlx_key_data_t key, float *dx,
			float *dy, t_game *gunstorm)
{
	if (key.key == MLX_KEY_W)
	{
		*dx = gunstorm->move_speed * cos(gunstorm->player.angle);
		*dy = gunstorm->move_speed * sin(gunstorm->player.angle);
	}
	if (key.key == MLX_KEY_S)
	{
		*dx = -gunstorm->move_speed * cos(gunstorm->player.angle);
		*dy = -gunstorm->move_speed * sin(gunstorm->player.angle);
	}
	if (key.key == MLX_KEY_D)
	{
		*dx = gunstorm->move_speed * cos(gunstorm->player.angle + M_PI_2);
		*dy = gunstorm->move_speed * sin(gunstorm->player.angle + M_PI_2);
	}
	if (key.key == MLX_KEY_A)
	{
		*dx = gunstorm->move_speed * cos(gunstorm->player.angle - M_PI_2);
		*dy = gunstorm->move_speed * sin(gunstorm->player.angle - M_PI_2);
	}
}

static bool	is_colliding(float x, float y, t_map map)
{
	float	dx;
	float	dy;
	float	offset;
	int		map_x;
	int		map_y;

	offset = 3.0;
	dx = -offset;
	while (dx <= offset)
	{
		dy = -offset;
		while (dy <= offset)
		{
			map_x = floorf((x + dx) / CELL_SIZE);
			map_y = floorf((y + dy) / CELL_SIZE);
			if (map_x >= 0 && map_y >= 0
				&& (map.rows[map_y][map_x] == '1'
				|| map.rows[map_y][map_x] == 'D'))
				return (true);
			dy += offset;
		}
		dx += offset;
	}
	return (false);
}

void	move_player(mlx_key_data_t key, t_player *player, t_game *gunstorm)
{
	float	new_x;
	float	new_y;

	move_in_playerdir(key, &new_x, &new_y, gunstorm);
	new_x += player->position.x;
	new_y += player->position.y;
	if (!is_colliding(new_x, player->position.y, gunstorm->map))
		player->position.x = new_x;
	if (!is_colliding(player->position.x, new_y, gunstorm->map))
		player->position.y = new_y;
}

void	player_movement(mlx_key_data_t key, t_game *gunstorm)
{
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_W))
		move_player(key, &gunstorm->player, gunstorm);
	else if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_S))
		move_player(key, &gunstorm->player, gunstorm);
	else if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_D))
		move_player(key, &gunstorm->player, gunstorm);
	else if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_A))
		move_player(key, &gunstorm->player, gunstorm);
}

void	game_hooks(mlx_key_data_t key, void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	player_movement(key, gunstorm);
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(gunstorm->mlx_data.mlx);
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_LEFT))
		gunstorm->player.angle -= 0.2;
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_RIGHT))
		gunstorm->player.angle += 0.2;
}
