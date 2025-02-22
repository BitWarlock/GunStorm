/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:53:20 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/22 15:53:22 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void	move_in_playerdir(t_direction direction, float *dx, float *dy,
		t_game *gunstorm)
{
	if (direction == FORWARD)
	{
		*dx = gunstorm->move_speed * cos(gunstorm->player.angle);
		*dy = gunstorm->move_speed * sin(gunstorm->player.angle);
	}
	if (direction == BACKWARD)
	{
		*dx = -gunstorm->move_speed * cos(gunstorm->player.angle);
		*dy = -gunstorm->move_speed * sin(gunstorm->player.angle);
	}
	if (direction == RIGHT)
	{
		*dx = gunstorm->move_speed * cos(gunstorm->player.angle + M_PI_2);
		*dy = gunstorm->move_speed * sin(gunstorm->player.angle + M_PI_2);
	}
	if (direction == LEFT)
	{
		*dx = gunstorm->move_speed * cos(gunstorm->player.angle - M_PI_2);
		*dy = gunstorm->move_speed * sin(gunstorm->player.angle - M_PI_2);
	}
}

static bool	is_colliding(float x, float y, t_map map)
{
	int	map_x;
	int	map_y;

	map_x = floorf(x / CELL_SIZE);
	map_y = floorf(y / CELL_SIZE);
	if (map_x >= 0 && map_y >= 0
		&& (map.rows[map_y][map_x] == '1'
		|| map.rows[map_y][map_x] == 'D'))
		return (true);
	map_x = floorf((x + 3.0) / CELL_SIZE);
	map_y = floorf((y + 3.0) / CELL_SIZE);
	if (map_x >= 0 && map_y >= 0
		&& (map.rows[map_y][map_x] == '1'
		|| map.rows[map_y][map_x] == 'D'))
		return (true);
	map_x = floorf((x - 3.0) / CELL_SIZE);
	map_y = floorf((y - 3.0) / CELL_SIZE);
	if (map_x >= 0 && map_y >= 0
		&& (map.rows[map_y][map_x] == '1'
		|| map.rows[map_y][map_x] == 'D'))
		return (true);
	return (false);
}

static void	move_player(t_direction direction,
				t_player *player, t_game *gunstorm)
{
	float	new_x;
	float	new_y;

	new_x = 0;
	new_y = 0;
	move_in_playerdir(direction, &new_x, &new_y, gunstorm);
	new_x += player->position.x;
	new_y += player->position.y;
	if (!is_colliding(new_x, player->position.y, gunstorm->map))
		player->position.x = new_x;
	if (!is_colliding(player->position.x, new_y, gunstorm->map))
		player->position.y = new_y;
}

void	player_movement(t_game *gunstorm, t_player *player)
{
	if (gunstorm->movement.forward)
		move_player(FORWARD, player, gunstorm);
	if (gunstorm->movement.backward)
		move_player(BACKWARD, player, gunstorm);
	if (gunstorm->movement.left)
		move_player(LEFT, player, gunstorm);
	if (gunstorm->movement.right)
		move_player(RIGHT, player, gunstorm);
}
