/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/13 11:10:02 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gunstorm.h"

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
			fatal_error("malloc", strerror(errno));
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
	print_gunstorm(gunstorm);
	close(fd);
}
