/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/14 12:02:44 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gunstorm.h"

static void	blocked_areas_warning(void)
{
	static int	count;

	if (count != 0)
		return ;
	count++;
	printf(MAG"Warning: Certain areas are"
		" inaccessible to the player\n"RESET);
}

static void	validate_player_access(t_game *gunstorm, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	flood_fill(gunstorm, &gunstorm->map,
		gunstorm->player.position);
	while (y < map->height)
	{
		x = 0;
		while (x < ft_strlen(map->rows[y]))
		{
			if (map->rows[y][x] == '0')
				blocked_areas_warning();
			if (map->rows[y][x] == 'x')
				map->rows[y][x] = '0';
			x++;
		}
		y++;
	}
}

static void	validate_position(t_game *gunstorm, t_map map, t_pair pos)
{
	if (pos.x <= 0 || pos.y <= 0
		|| pos.y >= map.height - 1
		|| pos.x >= (int)ft_strlen(map.rows[pos.y]) - 1)
		map_error_split("Map must be closed/surrounded by walls",
			gunstorm, NULL);
	if ((pos.x - 1 < (int)ft_strlen(map.rows[pos.y - 1])
			&& !valid_char(map.rows[pos.y][pos.x - 1]))
		|| (pos.x + 1 < (int)ft_strlen(map.rows[pos.y + 1])
		&& !valid_char(map.rows[pos.y][pos.x + 1]))
		|| !valid_char(map.rows[pos.y + 1][pos.x])
		|| !valid_char(map.rows[pos.y - 1][pos.x]))
		map_error_split("Map must be closed/surrounded by walls",
			gunstorm, NULL);
}

void	validate_map_walls(t_game *gunstorm, t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < ft_strlen(map.rows[y]))
		{
			if (map.rows[y][x] == '0' || player_char(map.rows[y][x]))
				validate_position(gunstorm, map, (t_pair){x, y});
			x++;
		}
		y++;
	}
	validate_player_access(gunstorm, &gunstorm->map);
}

void	store_player(t_game *gunstorm)
{
	int	y;
	int	x;

	y = 0;
	while (y < gunstorm->map.height)
	{
		x = 0;
		while (x < ft_strlen(gunstorm->map.rows[y]))
		{
			if (player_char(gunstorm->map.rows[y][x]))
			{
				gunstorm->player.direction = gunstorm->map.rows[y][x];
				gunstorm->player.position.x = x;
				gunstorm->player.position.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
