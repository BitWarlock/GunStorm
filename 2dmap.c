/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:06:21 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/18 18:06:57 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/gunstorm.h"

int	get_cell_color(char cell)
{
	if (cell == '0' || player_char(cell))
		return (0xFFFFFFFF);
	if (cell == '1')
		return (0x009e98cf);
	return (0x00000000);
}

void	draw_cube(mlx_image_t *img, int x, int y, char cell)
{
	int	i;
	int	j;

	i = 1;
	while (i < CELL_SIZE)
	{
		j = 1;
		while (j < CELL_SIZE)
		{
			mlx_put_pixel(img, x + i, y + j, get_cell_color(cell));
			j++;
		}
		i++;
	}
}

void	draw_player(mlx_image_t *img, t_pair position)
{
	int	i;
	int	j;

	i = 0;
	while (i < CELL_SIZE / 6)
	{
		j = 0;
		while (j < CELL_SIZE / 6)
		{
			mlx_put_pixel(img, position.x + i, position.y + j, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

size_t	map_width(t_map map)
{
	size_t	width;
	int		i;

	width = 0;
	i = 0;
	while (i < map.height)
	{
		if (ft_strlen(map.rows[i]) > width)
			width = ft_strlen(map.rows[i]);
		i++;
	}
	return (width);
}

void	game_fps(t_game *gunstorm)
{
	gunstorm->frames++;
	if (mlx_get_time() - gunstorm->start_time >= 1)
	{
		printf("FPS: %d\n", gunstorm->frames);
		gunstorm->frames = 0;
		gunstorm->start_time = mlx_get_time();
	}
}

void	draw_2d_map(t_game *gunstorm)
{
	int		i;
	int		j;

	i = 0;
	while (i < gunstorm->map.height)
	{
		j = 0;
		while (j < (int)ft_strlen(gunstorm->map.rows[i]))
		{
			draw_cube(gunstorm->mlx_data.img, j * CELL_SIZE,
				i * CELL_SIZE, gunstorm->map.rows[i][j]);
			j++;
		}
		i++;
	}
	draw_player(gunstorm->mlx_data.img, gunstorm->player.position);
}

void	map(void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	game_fps(gunstorm);
	draw_2d_map(gunstorm);
	raycaster(map_width(gunstorm->map) * CELL_SIZE, gunstorm, true);
}

void	map_2d(t_game *gunstorm)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(map_width(gunstorm->map) * CELL_SIZE,
			gunstorm->map.height * CELL_SIZE, "GunStorm", true);
	if (!mlx)
		(free_all(gunstorm)), exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, map_width(gunstorm->map) * CELL_SIZE,
			gunstorm->map.height * CELL_SIZE);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		(free_all(gunstorm)), mlx_terminate(mlx),
			exit(EXIT_FAILURE);
	gunstorm->mlx_data.mlx = mlx;
	gunstorm->mlx_data.img = img;
	gunstorm->start_time = mlx_get_time();
	gunstorm->frames = 0;
	mlx_loop_hook(gunstorm->mlx_data.mlx, map, gunstorm);
	mlx_key_hook(gunstorm->mlx_data.mlx, game_hooks, gunstorm);
	mlx_loop(gunstorm->mlx_data.mlx);
	mlx_terminate(gunstorm->mlx_data.mlx);
}
