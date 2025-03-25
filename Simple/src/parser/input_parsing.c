/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/25 03:29:34 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static float	player_angle(char direction)
{
	if (direction == 'S')
		return (M_PI / 2);
	if (direction == 'N')
		return (3 * M_PI / 2);
	if (direction == 'W')
		return (M_PI);
	return (0);
}

void	store_player(t_game *gunstorm)
{
	int		y;
	size_t	x;

	y = 0;
	while (y < gunstorm->map.height)
	{
		x = 0;
		while (x < ft_strlen(gunstorm->map.rows[y]))
		{
			if (player_char(gunstorm->map.rows[y][x]))
			{
				gunstorm->player.angle = player_angle(gunstorm->map.rows[y][x]);
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

static char	*get_map_content(int map_fd)
{
	char	*map;
	char	*str;
	char	*tmp;

	map = ft_strdup("");
	if (!map)
		fatal_error("malloc", strerror(errno));
	str = get_next_line(map_fd);
	while (str)
	{
		tmp = map;
		map = ft_strjoin(map, str);
		if (!map)
			(free(tmp), fatal_error("malloc", strerror(errno)));
		free(tmp);
		free(str);
		str = get_next_line(map_fd);
	}
	return (map);
}

static void	validate_scene_file(int map_fd, t_game *gunstorm)
{
	char	*map;

	map = get_map_content(map_fd);
	validate_identifiers(map, gunstorm);
	validate_textures(map, gunstorm);
	validate_colors(map, gunstorm);
	validate_map(map, gunstorm);
}

void	input_parsing(char *map_file, t_game *gunstorm)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	validate_scene_file(fd, gunstorm);
	close(fd);
}
