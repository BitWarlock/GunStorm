/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/13 11:10:02 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gunstorm.h"

static bool	is_within_bounds(t_map *map, t_pair pos)
{
	return (pos.x >= 0 && pos.y >= 0
		&& pos.y < map->height
		&& pos.x < (int)ft_strlen(map->rows[pos.y]));
}

static bool	is_invalid_cell(t_map *map, t_pair pos)
{
	char	cell;

	cell = map->rows[pos.y][pos.x];
	if (cell == '1' || cell == 'x')
		return (true);
	if (cell != '0' && !player_char(cell))
		return (true);
	return (false);
}

static bool	is_adjacent_valid(t_map *map, t_pair pos)
{
	if (pos.x <= 0 || pos.y <= 0
		|| pos.y >= map->height - 1
		|| pos.x >= (int)ft_strlen(map->rows[pos.y]) - 1)
		return (false);
	if (pos.x - 1 < (int)ft_strlen(map->rows[pos.y - 1])
		&& map->rows[pos.y][pos.x - 1] == ' ')
		return (false);
	if (pos.x + 1 < (int)ft_strlen(map->rows[pos.y + 1])
		&& map->rows[pos.y][pos.x + 1] == ' ')
		return (false);
	if (map->rows[pos.y + 1][pos.x] == ' '
		|| map->rows[pos.y - 1][pos.x] == ' ')
		return (false);
	return (true);
}

static bool	is_valid_position(t_map *map, t_pair pos)
{
	if (pos.y > 0 && pos.x >= (int)ft_strlen(map->rows[pos.y - 1]))
		return (false);
	if (pos.y < map->height - 1
		&& pos.x >= (int)ft_strlen(map->rows[pos.y + 1]))
		return (false);
	if (!is_adjacent_valid(map, pos))
		return (false);
	return (true);
}

void	flood_fill(t_game *gunstorm, t_map *map, t_pair pos)
{
	if (!is_within_bounds(map, pos))
		map_error_split("Map must be closed/surrounded by walls",
			gunstorm, NULL);
	if (is_invalid_cell(map, pos))
		return ;
	if (!is_valid_position(map, pos))
		map_error_split("Map must be closed/surrounded by walls",
			gunstorm, NULL);
	if (map->rows[pos.y][pos.x] == '0')
		map->rows[pos.y][pos.x] = 'x';
	flood_fill(gunstorm, map, (t_pair){pos.x - 1, pos.y});
	flood_fill(gunstorm, map, (t_pair){pos.x + 1, pos.y});
	flood_fill(gunstorm, map, (t_pair){pos.x, pos.y - 1});
	flood_fill(gunstorm, map, (t_pair){pos.x, pos.y + 1});
}
