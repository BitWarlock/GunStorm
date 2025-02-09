/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:42:54 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/09 17:03:55 by agaladi          ###   ########.fr       */
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
		&& (map.rows[map_y][map_x] == '1'
		|| map.rows[map_y][map_x] == 'D'))
		return (true);
	map_x = floorf((x + 1.9) / CELL_SIZE);
	map_y = floorf((y + 1.9) / CELL_SIZE);
	if (map_x >= 0 && map_y >= 0
		&& (map.rows[map_y][map_x] == '1'
		|| map.rows[map_y][map_x] == 'D'))
		return (true);
	map_x = floorf((x - 1.9) / CELL_SIZE);
	map_y = floorf((y - 1.9) / CELL_SIZE);
	if (map_x >= 0 && map_y >= 0
		&& (map.rows[map_y][map_x] == '1'
		|| map.rows[map_y][map_x] == 'D'))
		return (true);
	return (false);
}

void	move_player(mlx_key_data_t key, t_player *player, t_game *gunstorm)
{
	float	new_x;
	float	new_y;

	new_x = 0;
	new_y = 0;
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


void	door_open_close(t_map *map, t_pair player)
{
	int	x;
	int	y;

	x = floor(player.x / CELL_SIZE);
	y = floor(player.y / CELL_SIZE);
	if (map->rows[y - 1][x] == 'D')
		map->rows[y - 1][x] = 'O';
	else if (map->rows[y + 1][x] == 'D')
		map->rows[y + 1][x] = 'O';
	else if (map->rows[y][x + 1] == 'D')
		map->rows[y][x + 1] = 'O';
	else if (map->rows[y][x - 1] == 'D')
		map->rows[y][x - 1] = 'O';
	else if (map->rows[y - 1][x] == 'O')
		map->rows[y - 1][x] = 'D';
	else if (map->rows[y + 1][x] == 'O')
		map->rows[y + 1][x] = 'D';
	else if (map->rows[y][x + 1] == 'O')
		map->rows[y][x + 1] = 'D';
	else if (map->rows[y][x - 1] == 'O')
		map->rows[y][x - 1] = 'D';
}



void	game_hooks(mlx_key_data_t key, void *param)
{
	t_game	*gunstorm;
	int		current_frame;

	gunstorm = (t_game *)param;
	gunstorm->start_game = true;
	gunstorm->mlx_data.welcome_screen->enabled = false;
	player_movement(key, gunstorm);
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_ESCAPE))
	{
		current_frame = gunstorm->player_anim.current_frame;
		gunstorm->player_anim.frames[current_frame]->enabled = true;
		gunstorm->menu = !gunstorm->menu;
	}
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_LEFT))
		gunstorm->player.angle -= 0.1;
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_RIGHT))
		gunstorm->player.angle += 0.1;
	if (infront_door(gunstorm->map, gunstorm->player.position)
		&& mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_O))
		door_open_close(&gunstorm->map, gunstorm->player.position);
}
