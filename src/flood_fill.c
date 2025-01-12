#include "../include/gunstorm.h"

bool	is_within_bounds(t_map *map, t_pair pos)
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

bool	valid_char(char a)
{
	return (a == '1'
		|| a == '0' || a == 'E'
		|| a == 'W' || a == 'N'
		|| a == 'S');
}

void	validate_position(t_game *gunstorm, t_map map, t_pair pos)
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
}
