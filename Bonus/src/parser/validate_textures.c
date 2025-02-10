/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/08 12:57:13 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

void	validate_doors(t_game *gunstorm, t_map map, int x, int y)
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

static char	*get_file_name(char *str, char *texture)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*file;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	tmp = ft_substr(str, 0, i);
	file = ft_strtrim(tmp, " \n\t");
	if (!tmp || !file)
		fatal_error("malloc", strerror(errno));
	free(tmp);
	fd = open(file, O_RDONLY);
	if (fd != -1)
		return (file);
	return (free(file), NULL);
}

static void	fill_texture_file(t_game *gunstorm,
								mlx_texture_t *texture_, char texture)
{
	if (texture == 'N')
		gunstorm->texture.north = texture_;
	if (texture == 'S')
		gunstorm->texture.south = texture_;
	if (texture == 'W')
		gunstorm->texture.west = texture_;
	if (texture == 'E')
		gunstorm->texture.east = texture_;
}

static char	*find_substr(char *str, char *substr)
{
	char	*next_tmp;
	char	*file;
	char	*tmp;
	int		start;

	tmp = ft_strdup(str);
	if (!tmp)
		fatal_error("malloc", strerror(errno));
	start = find(tmp, substr);
	while (start != -1)
	{
		file = get_file_name(tmp + start + 2, substr);
		if (file)
			return (free(tmp), file);
		next_tmp = ft_substr(tmp, start + 2, ft_strlen(tmp));
		if (!next_tmp)
			fatal_error("malloc", strerror(errno));
		free(tmp);
		tmp = next_tmp;
		start = find(tmp, substr);
	}
	return (free(tmp), NULL);
}

void	validate_textures(char *map, t_game *gunstorm)
{
	mlx_texture_t	*texture;
	char			*textures[5];
	char			*file;
	int				start;
	int				i;

	textures[0] = "NO";
	textures[1] = "SO";
	textures[2] = "WE";
	textures[3] = "EA";
	i = 0;
	while (i < 4)
	{
		file = find_substr(map, textures[i]);
		texture = mlx_load_png(file);
		free(file);
		if (!file || !texture)
			(free_textures(map, gunstorm, i)), texture_error(textures[i]);
		fill_texture_file(gunstorm, texture, textures[i][0]);
		i++;
	}
	gunstorm->texture.door = mlx_load_png("./texture/door.png");
}
