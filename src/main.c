#include "../include/gunstorm.h"
#include <errno.h>

void	free_game(t_game *gunstorm);

#define RED "\e[0;31m"
#define RESET "\e[0m"

bool	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\n');
}

int	find(char *str, char *substr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str + i, substr, ft_strlen(substr)))
			return (i);
		i++;
	}
	return (-1);
}

void	texture_error(char *error)
{
	ft_printf(2, RED"Error\n");
	ft_printf(2, "%s texture file either missing or invalid\n"RESET, error);
	exit(EXIT_FAILURE);
}

void	fatal_error(char *error, char *msg)
{
	ft_printf(2, RED"Error\n");
	if (!msg)
		ft_printf(2, "%s\n"RESET, error);
	else
		ft_printf(2, "%s: %s\n"RESET, error, msg);
	exit(EXIT_FAILURE);
}

char	*get_file_name(char *str, char *texture)
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

char	*find_substr(char *str, char *substr)
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

void	fill_texture_file(t_game *gunstorm, char *file, char texture)
{
	if (texture == 'N')
		gunstorm->texture.north = file;
	if (texture == 'S')
		gunstorm->texture.south = file;
	if (texture == 'W')
		gunstorm->texture.west = file;
	if (texture == 'E')
		gunstorm->texture.east = file;
}

void	free_textures(char *map, t_game *gunstorm, int index)
{
	if (index >= 1)
		free(gunstorm->texture.north);
	if (index >= 2)
		free(gunstorm->texture.south);
	if (index >= 3)
		free(gunstorm->texture.west);
	free(gunstorm);
	free(map);
}

void	validate_textures(char *map, t_game *gunstorm)
{
	char	*textures[5];
	char	*file;
	int		start;
	int		i;

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
		fill_texture_file(gunstorm, file, textures[i][0]);
		i++;
	}
}

char	*get_map_content(int map_fd)
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

void	free_game(t_game *gunstorm)
{
	free(gunstorm->texture.north);
	free(gunstorm->texture.east);
	free(gunstorm->texture.south);
	free(gunstorm->texture.west);
	free(gunstorm);
}

char	*get_color_line(char *map)
{
	int		i;
	int		comma;
	char	*line;

	i = 0;
	comma = 0;
	while (map[i] && map[i] != '\n')
		i++;
	line = ft_substr(map, 0, i);
	i = -1;
	while (line[++i])
		if (line[i] == ',')
			comma++;
	if (comma == 2)
		return (line);
	return (free(line), NULL);
}

char	*find_color_values(char *map, char *substr)
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
			fatal_error("malloc", strerror(errno));
		free(tmp);
		tmp = next_tmp;
		start = find(tmp, substr);
	}
	return (free(tmp), NULL);
}

char	*color_string(char *color)
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

int	color_value(char *color)
{
	int		value;
	char	*color_value;

	color_value = color_string(color);
	if (!color_value || !color_value[0]
		|| ft_strlen(color_value) > 3)
		return (free(color_value), -1);
	value = ft_atoi(color);
	return (free(color_value), value);
}

void	free_split(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

t_rgb	get_color_values(char *line)
{
	t_rgb	values;
	char	**colors;

	colors = ft_split(line, ',');
	if (!colors)
		(free(line)), fatal_error("malloc", strerror(errno));
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

void	print_gunstorm(t_game *gunstorm)
{
	printf("Textures:\n\nNorth: %s\nSouth: %s\nWest: %s\nEast: %s\n\n",
		gunstorm->texture.north, gunstorm->texture.south,
		gunstorm->texture.west, gunstorm->texture.east);
	printf("Ceiling color:\t(%3d, %3d, %3d)\n", gunstorm->ceiling.r,
		gunstorm->ceiling.g, gunstorm->ceiling.b);
	printf("Floor color:\t(%3d, %3d, %3d)\n", gunstorm->floor.r,
		gunstorm->floor.g, gunstorm->floor.b);
	for (int i = 0; gunstorm->map.rows[i]; i++)
		printf("Row %d => %s\n", i, gunstorm->map.rows[i]);
}

bool	valid_map_char(char a)
{
	return (a == ' ' || a == '1'
		|| a == '0' || a == 'E'
		|| a == 'W' || a == 'N'
		|| a == 'S');
}

bool	empty_line(char *line, int s)
{
	while (line[s] && line[s] != '\n')
	{
		if (line[s] != ' ')
			return (false);
		s++;
	}
	return (true);
}

int	check_line(char *line, int s)
{
	int	i;

	if (empty_line(line, s))
		return (-1);
	i = s;
	while (line[i] && line[i] != '\n')
	{
		if (!valid_map_char(line[i]))
			return (-1);
		i++;
	}
	return (s);
}

bool	player_char(char a)
{
	return (a == 'E'
		|| a == 'S' || a == 'W'
		|| a == 'N');
}

char	*trim_map(char *map)
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
	new_map = ft_substr(map, 0, e + 1);
	free(map);
	return (new_map);
}

char	*get_map(char *scene)
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
	return (trim_map(ft_strtrim(scene + start, "\n")));
}

void	map_error(char *error_msg,
			t_game *gunstorm, char *map)
{
	free_game(gunstorm);
	free(map);
	ft_printf(2, RED"Error\n");
	ft_printf(2, "Map error: %s\n"RESET, error_msg);
	exit(EXIT_FAILURE);
}

void	store_player(t_game *gunstorm)
{
	int	y;
	int	x;

	y = 0;
	while (y < gunstorm->map.height)
	{
		x = 0;
		while (x < ft_strlen(gunstorm->map.rows[y]))
		{
			if (player_char(gunstorm->map.rows[y][x]))
			{
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

int	validate_map_chars(char *map, t_game *gunstorm)
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
			map_error("Invalid character detected. Map should only contain:\n"
				"- 0 for empty space\n"
				"- 1 for walls\n"
				"- N, E, S, or W for player direction", gunstorm, map);
		i++;
	}
	return (player);
}

void	load_map(char *map, t_game *gunstorm)
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

void	map_error_split(char *error_msg, t_game *gunstorm, char *map)
{
	free_split(gunstorm->map.rows);
	map_error(error_msg, gunstorm, map);
}

void	validate_map(char *scene, t_game *gunstorm)
{
	int		player;
	char	*map;

	map = get_map(scene);
	free(scene);
	if (!map)
		map_error("Empty map", gunstorm, map);
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

void	free_all(t_game *gunstorm)
{
	free_split(gunstorm->map.rows);
	free_game(gunstorm);
}

void	map_content_validation(int map_fd, t_game *gunstorm)
{
	char	*map;

	map = get_map_content(map_fd);
	validate_textures(map, gunstorm);
	validate_colors(map, gunstorm);
	validate_map(map, gunstorm);
}

void	input_validation(char *argv[])
{
	char	*ext;
	int		fd;

	if (!argv[1])
		fatal_error("No map file found.\nUsage: ./cub3D ./map_file.cub", 0);
	if (argv[2])
		fatal_error("Too many arguments.\nUsage: ./cub3D ./map_file.cub", 0);
	ext = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4);
	if (ft_strncmp(ext, ".cub", 4))
		(free(ext)), fatal_error("The file extension must be '.cub'", 0);
	free(ext);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		fatal_error(argv[1], strerror(errno));
	close(fd);
}

void	validate_player_access(t_game *gunstorm, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	flood_fill(gunstorm, &gunstorm->map,
		gunstorm->player.position);
	while (y < map->height)
	{
		x = 0;
		while (x < ft_strlen(map->rows[y]))
		{
			if (map->rows[y][x] == '0')
			{
				printf(MAG"Warning: Certain areas are"
					"inaccessible to the player\n"RESET);
				return ;
			}
			if (map->rows[y][x] == 'x')
				map->rows[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	input_parsing(char *map_file, t_game *gunstorm)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	map_content_validation(fd, gunstorm);
	validate_player_access(gunstorm, &gunstorm->map);
	print_gunstorm(gunstorm);
	close(fd);
}

void	start_game(char *map_file)
{
	t_game	*gunstorm;

	gunstorm = malloc(sizeof(t_game));
	if (!gunstorm)
		fatal_error("malloc", strerror(errno));
	input_parsing(map_file, gunstorm);
	free_all(gunstorm);
}

int	main(int argc, char *argv[])
{
	input_validation(argv);
	start_game(argv[1]);
	return (EXIT_SUCCESS);
}
