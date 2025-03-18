/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/18 05:52:16 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static char	*find_color_values(char *map, char *substr)
{
	char	*next_tmp;
	char	*file;
	char	*tmp;
	int		start;

	tmp = ft_strdup(map);
	if (!tmp)
		fatal_error("malloc", strerror(errno));
	start = find(tmp, substr);
	while (start != -1)
	{
		file = get_color_line(tmp + start + 1);
		if (file)
			return (free(tmp), file);
		next_tmp = ft_substr(tmp, start + 1, ft_strlen(tmp));
		if (!next_tmp)
			(free(tmp), fatal_error("malloc", strerror(errno)));
		free(tmp);
		tmp = next_tmp;
		start = find(tmp, substr);
	}
	return (free(tmp), NULL);
}

static char	*color_string(char *color)
{
	int	i;
	int	e;
	int	s;

	s = 0;
	while (color[s] && (color[s] == ' ' || color[s] == '\t'))
		s++;
	e = s;
	while (color[e] && ft_isdigit(color[e]))
		e++;
	i = e;
	while (color[i] && (color[i] == ' ' || color[i] == '\t'))
		i++;
	if (color[i] != '\0')
		return (NULL);
	return (ft_substr(color, s, e - s));
}

static int	color_value(char *color)
{
	int		value;
	char	*color_value;

	color_value = color_string(color);
	if (!color_value || !color_value[0]
		|| ft_strlen(color_value) > 3)
		return (free(color_value), -1);
	value = ft_atoi(color_value);
	return (free(color_value), value);
}

static t_rgb	get_color_values(char *line)
{
	t_rgb	values;
	char	**colors;

	if (!line)
		return ((t_rgb){-1, -1, -1});
	colors = ft_split(line, ',');
	if (!colors)
		return (free(line)), (t_rgb){-1, -1, -1};
	if (!colors[0] || !colors[1] || !colors[2])
		return (free(line), free_split(colors), (t_rgb){-1, -1, -1});
	values.r = color_value(colors[0]);
	values.g = color_value(colors[1]);
	values.b = color_value(colors[2]);
	if (values.r > 255 || values.r < 0
		|| values.g > 255 || values.g < 0
		|| values.b > 255 || values.b < 0)
		return (free(line), free_split(colors), (t_rgb){-1, -1, -1});
	return (free(line), free_split(colors), values);
}

void	validate_colors(char *map, t_game *gunstorm)
{
	t_rgb	floor;
	t_rgb	ceiling;

	floor = get_color_values(find_color_values(map, "F"));
	if (floor.r == -1)
		(free_game(gunstorm)), free(map),
			fatal_error("Floor color either missing or invalid", 0);
	ceiling = get_color_values(find_color_values(map, "C"));
	if (ceiling.r == -1)
		(free_game(gunstorm)), free(map),
			fatal_error("Ceiling color either missing or invalid", 0);
	gunstorm->floor = floor;
	gunstorm->ceiling = ceiling;
}
