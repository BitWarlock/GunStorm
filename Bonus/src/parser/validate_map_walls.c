/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/22 16:09:51 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void	validate_player_access(t_game *gunstorm, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	flood_fill(gunstorm, &gunstorm->map,
		gunstorm->player.position.x, gunstorm->player.position.y);
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

static void	validate_position(t_game *gunstorm, t_map map, int x, int y)
{
	if (x <= 0 || y <= 0
		|| y >= map.height - 1
		|| x >= (int)ft_strlen(map.rows[y]) - 1)
		map_error_split("Map must be closed/surrounded by walls",
			gunstorm, NULL);
	if ((x - 1 < (int)ft_strlen(map.rows[y - 1])
			&& !valid_char(map.rows[y][x - 1]))
		|| (x + 1 < (int)ft_strlen(map.rows[y + 1])
		&& !valid_char(map.rows[y][x + 1]))
		|| !valid_char(map.rows[y + 1][x])
		|| !valid_char(map.rows[y - 1][x]))
		map_error_split("Map must be closed/surrounded by walls",
			gunstorm, NULL);
}

static void	validate_door_adjacent(t_game *gunstorm, int x, int y, char axis)
{
	t_map	map;

	map = gunstorm->map;
	if (axis == 'x')
	{
		if ((map.rows[y][x - 1] != '0'
			&& !player_char(map.rows[y][x - 1]))
			|| (map.rows[y][x + 1] != '0'
			&& !player_char(map.rows[y][x + 1])))
			map_error_split("Door must have adjacent empty spaces",
				gunstorm, NULL);
	}
	if (axis == 'y')
	{
		if ((map.rows[y - 1][x] != '0'
			&& !player_char(map.rows[y - 1][x]))
			|| (map.rows[y + 1][x] != '0'
			&& !player_char(map.rows[y + 1][x])))
			map_error_split("Door must have adjacent empty spaces",
				gunstorm, NULL);
	}
}

static void	validate_doors(t_game *gunstorm, t_map map, int x, int y)
{
	if (x <= 0 || y <= 0
		|| y >= map.height - 1
		|| x >= (int)ft_strlen(map.rows[y]) - 1)
		map_error_split("Door position is not valid",
			gunstorm, NULL);
	if (map.rows[y - 1][x] == '1')
	{
		if (map.rows[y + 1][x] != '1')
			map_error_split("Door must be surrounded by walls",
				gunstorm, NULL);
		validate_door_adjacent(gunstorm, x, y, 'x');
	}
	else if (map.rows[y][x - 1] == '1')
	{
		if (map.rows[y][x + 1] != '1')
			map_error_split("Door must be surrounded by walls",
				gunstorm, NULL);
		validate_door_adjacent(gunstorm, x, y, 'y');
	}
	else
		map_error_split("Door must be adjacent to a wall",
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
			if (map.rows[y][x] == 'D')
				validate_doors(gunstorm, map, x, y);
			if (map.rows[y][x] == '0' || player_char(map.rows[y][x]))
				validate_position(gunstorm, map, x, y);
			x++;
		}
		y++;
	}
	validate_player_access(gunstorm, &gunstorm->map);
}
