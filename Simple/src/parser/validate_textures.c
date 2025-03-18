/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/18 21:51:48 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static char	*get_file_name(char *str)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*file;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	tmp = ft_substr(str, 0, i);
	if (!tmp)
		fatal_error("malloc", strerror(errno));
	file = ft_strtrim(tmp, " \n\t");
	free(tmp);
	if (!file)
		fatal_error("malloc", strerror(errno));
	fd = open(file, O_RDONLY);
	if (fd != -1)
		return (close(fd), file);
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
		file = get_file_name(tmp + start + 2);
		if (file)
			return (free(tmp), file);
		next_tmp = ft_substr(tmp, start + 2, ft_strlen(tmp));
		if (!next_tmp)
			(free(tmp), fatal_error("malloc", strerror(errno)));
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
	int				i;

	textures[0] = "NO";
	textures[1] = "SO";
	textures[2] = "WE";
	textures[3] = "EA";
	i = 0;
	while (i < 4)
	{
		file = find_substr(map, textures[i]);
		if (!file)
			(free_textures(map, gunstorm, i)), texture_error(textures[i]);
		texture = mlx_load_png(file);
		if (!texture)
			(free_textures(map, gunstorm, i)),
				free(file), texture_error(textures[i]);
		free(file);
		fill_texture_file(gunstorm, texture, textures[i][0]);
		i++;
	}
}
