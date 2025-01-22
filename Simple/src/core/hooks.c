/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:42:54 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/22 17:20:16 by mrezki           ###   ########.fr       */
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

bool	is_colliding(float x, float y, t_map map)
{
	int	map_x;
	int	map_y;

	map_x = floorf(x / CELL_SIZE);
	map_y = floorf(y / CELL_SIZE);
	if (map_x >= 0 && map_y >= 0
		&& map.rows[map_y][map_x] == '1')
		return (true);
	map_x = floorf((x + 1.9) / CELL_SIZE);
	map_y = floorf((y + 1.9) / CELL_SIZE);
	if (map_x >= 0 && map_y >= 0
		&& map.rows[map_y][map_x] == '1')
		return (true);
	map_x = floorf((x - 1.9) / CELL_SIZE);
	map_y = floorf((y - 1.9) / CELL_SIZE);
	if (map_x >= 0 && map_y >= 0
		&& map.rows[map_y][map_x] == '1')
		return (true);
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
		gunstorm->player.angle -= 0.1;
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_RIGHT))
		gunstorm->player.angle += 0.1;
}
