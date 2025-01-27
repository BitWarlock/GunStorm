/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/22 17:20:16 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

void	print_gunstorm(t_game *gunstorm)
{
	int	i;

	i = -1;
	printf("Ceiling color:\t(%3d, %3d, %3d)\n", gunstorm->ceiling.r,
		gunstorm->ceiling.g, gunstorm->ceiling.b);
	printf("Floor color:\t(%3d, %3d, %3d)\n", gunstorm->floor.r,
		gunstorm->floor.g, gunstorm->floor.b);
	while (gunstorm->map.rows[++i])
		printf("Row %3d =>\t%s\n", i, gunstorm->map.rows[i]);
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

int	main(int argc, char *argv[])
{
	input_validation(argv);
	game_core(argv[1]);
	return (EXIT_SUCCESS);
}
