/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:53:20 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/22 02:43:55 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm_bonus.h"

static void	move_in_playerdir(t_direction direction, float *dx, float *dy,
		t_game *gunstorm)
{
	int	angle;

	angle = gunstorm->player.angle_degree;
	if (direction == FORWARD)
	{
		*dx = gunstorm->move_speed * gunstorm->cos_table[angle];
		*dy = gunstorm->move_speed * gunstorm->sin_table[angle];
	}
	else if (direction == BACKWARD)
	{
		*dx = -gunstorm->move_speed * gunstorm->cos_table[angle];
		*dy = -gunstorm->move_speed * gunstorm->sin_table[angle];
	}
	else if (direction == RIGHT)
	{
		angle = (angle + 900) % 3600;
		*dx = gunstorm->move_speed * gunstorm->cos_table[angle];
		*dy = gunstorm->move_speed * gunstorm->sin_table[angle];
	}
	else if (direction == LEFT)
	{
		angle = (angle - 900 + 3600) % 3600;
		*dx = gunstorm->move_speed * gunstorm->cos_table[angle];
		*dy = gunstorm->move_speed * gunstorm->sin_table[angle];
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
