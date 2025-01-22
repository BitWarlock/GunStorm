/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/22 17:20:24 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static bool	is_within_bounds(t_map *map, int x, int y)
{
	return (x >= 0 && y >= 0
		&& y < map->height
		&& x < (int)ft_strlen(map->rows[y]));
}

static bool	is_invalid_cell(t_map *map, int x, int y)
{
	char	cell;

	cell = map->rows[y][x];
	if (cell == '1' || cell == 'x')
		return (true);
	if (cell != '0' && !player_char(cell))
		return (true);
	return (false);
}

static bool	is_adjacent_valid(t_map *map, int x, int y)
{
	if (x <= 0 || y <= 0
		|| y >= map->height - 1
		|| x >= (int)ft_strlen(map->rows[y]) - 1)
		return (false);
	if (x - 1 < (int)ft_strlen(map->rows[y - 1])
		&& map->rows[y][x - 1] == ' ')
		return (false);
	if (x + 1 < (int)ft_strlen(map->rows[y + 1])
		&& map->rows[y][x + 1] == ' ')
		return (false);
	if (map->rows[y + 1][x] == ' '
		|| map->rows[y - 1][x] == ' ')
		return (false);
	return (true);
}

static bool	is_valid_tion(t_map *map, int x, int y)
{
	if (y > 0 && x >= (int)ft_strlen(map->rows[y - 1]))
		return (false);
	if (y < map->height - 1
		&& x >= (int)ft_strlen(map->rows[y + 1]))
		return (false);
	if (!is_adjacent_valid(map, x, y))
		return (false);
	return (true);
}

void	flood_fill(t_game *gunstorm, t_map *map, int x, int y)
{
	if (!is_within_bounds(map, x, y))
		map_error_split("Map must be closed/surrounded by walls",
			gunstorm, NULL);
	if (is_invalid_cell(map, x, y))
		return ;
	if (!is_valid_tion(map, x, y))
		map_error_split("Map must be closed/surrounded by walls",
			gunstorm, NULL);
	if (map->rows[y][x] == '0')
		map->rows[y][x] = 'x';
	flood_fill(gunstorm, map, x - 1, y);
	flood_fill(gunstorm, map, x + 1, y);
	flood_fill(gunstorm, map, x, y - 1);
	flood_fill(gunstorm, map, x, y + 1);
}
