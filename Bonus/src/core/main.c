/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/21 03:25:04 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

void	game_fps(t_game *gunstorm)
{
	gunstorm->move_speed = 30.0 * gunstorm->mlx_data.mlx->delta_time;
	gunstorm->frames++;
	if (mlx_get_time() - gunstorm->start_time >= 1)
	{
		printf("FPS: %d\n", gunstorm->frames);
		gunstorm->frames = 0;
		gunstorm->start_time = mlx_get_time();
	}
}

void	game_init_lookup_t(t_game *gunstorm)
{
	int		i;
	float	angle;

	i = 0;
	while (i < 3600)
	{
		angle = (float)i * M_PI / 1800.0f;
		gunstorm->cos_table[i] = cos(angle);
		gunstorm->sin_table[i] = sin(angle);
		i++;
	}
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
