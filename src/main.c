#include "../include/gunstorm.h"
#include <errno.h>

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
	ft_printf(2, "%s texture file not provided\n"RESET, error);
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

void	validate_file(char *str, char *texture)
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
	free(tmp);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		fatal_error(file, strerror(errno));
	free(file);
}

void	validate_textures(char *str)
{
	int		start;
	int		i;
	char	*textures[5];

	textures[0] = "NO";
	textures[1] = "SO";
	textures[2] = "WE";
	textures[3] = "EA";
	i = 0;
	while (i < 4)
	{
		start = find(str, textures[i]);
		if (start != -1)
			validate_file(str + start + 2, textures[i]);
		else
			texture_error(textures[i]);
		i++;
	}
}

void	map_validation(int map_fd)
{
	char	*map;
	char	*str;
	char	*tmp;

	map = ft_strdup("");
	if (!map)
		return;
	str = get_next_line(map_fd);
	while (str)
	{
		tmp = map;
		map = ft_strjoin(map, str);
		free(tmp);
		free(str);
		str = get_next_line(map_fd);
	}
	/*printf("map\n%s", map);*/
	validate_textures(map);
	free(map);
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
		fatal_error("The file extension must be '.cub'", 0);
	free(ext);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		fatal_error(argv[1], strerror(errno));
	map_validation(fd);
	close(fd);
}

int	main(int argc, char *argv[])
{
	input_validation(argv);
	/*input_parsing();*/
	return EXIT_SUCCESS;
}
