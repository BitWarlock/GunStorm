/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/29 11:15:53 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static int	validate_map_chars(char *map, t_game *gunstorm)
{
	int	player;
	int	i;

	i = 0;
	player = 0;
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
			map_error("Empty lines not allowed", gunstorm, map);
		if (player_char(map[i]))
			player++;
		if (!valid_map_char(map[i]) && map[i] != '\n')
			map_error("Invalid character detected.\nMap should only contain:\n"
				"- 0 for empty space\n"
				"- 1 for walls\n"
				"- ' ' for empty areas\n"
				"- 'D' for doors\n"
				"- N, E, S, or W for player direction", gunstorm, map);
		i++;
	}
	return (player);
}

static char	*trim_map(char *map, t_game *gunstorm)
{
	char	*new_map;
	int		e;
	int		i;

	i = ft_strlen(map) - 1;
	while (map[i])
	{
		if (map[i] == '1' || map[i] == '0')
		{
			e = i;
			break ;
		}
		i--;
	}
	while (map[++i])
	{
		if (!is_space(map[i]))
			map_error("The map has to be the last element",
				gunstorm, map);
	}
	new_map = ft_substr(map, 0, e + 1);
	free(map);
	return (new_map);
}

static char	*get_map(char *scene)
{
	int	start;
	int	i;

	i = 0;
	start = -1;
	while (scene[i])
	{
		if (scene[i] == '\n')
			start = check_line(scene, i + 1);
		if (start != -1)
			break ;
		i++;
	}
	if (start == -1)
		return (NULL);
	return (ft_strtrim(scene + start, "\n"));
}

static void	load_map(char *map, t_game *gunstorm)
{
	char	**rows;
	int		i;

	i = 0;
	rows = ft_split(map, '\n');
	if (!rows)
		map_error("Malloc failed", gunstorm, map);
	while (rows[i])
		i++;
	gunstorm->map.rows = rows;
	gunstorm->map.height = i;
}

void	validate_map(char *scene, t_game *gunstorm)
{
	int		player;
	char	*map;

	map = get_map(scene);
	free(scene);
	if (!map)
		map_error("Empty map", gunstorm, map);
	map = trim_map(map, gunstorm);
	player = validate_map_chars(map, gunstorm);
	if (player == 0)
		map_error("Missing player start position", gunstorm, map);
	if (player > 1)
		map_error("Multiple player positions found", gunstorm, map);
	load_map(map, gunstorm);
	free(map);
	store_player(gunstorm);
	validate_map_walls(gunstorm, gunstorm->map);
}
