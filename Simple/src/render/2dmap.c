/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:06:21 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/24 15:46:56 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

void	ray_draw_line(t_game *gunstorm, mlx_image_t *img, float x, float y)
{
	int		i;
	float	dx;
	float	dy;
	float	step;

	dx = gunstorm->ray.wall_x * CELL_SIZE - gunstorm->player.position.x;
	dy = gunstorm->ray.wall_y * CELL_SIZE - gunstorm->player.position.y;
	step = fmax(fabs(dx), fabs(dy));
	dx /= step;
	dy /= step;
	i = 0;
	while (i <= step)
	{
		if (x >= 0 && x < img->width
			&& y >= 0 && y < img->height)
			mlx_put_pixel(img, (int)x, (int)y, 0x000000FF);
		x += dx;
		y += dy;
		i++;
	}
}

static void	draw_cube(mlx_image_t *img, int x, int y, char cell)
{
	int	color;
	int	i;
	int	j;

	i = 1;
	if (cell == '0' || player_char(cell))
		color = (0xFFFFFFFF);
	else if (cell == '1')
		color = (0x009e98cf);
	else
		color = (0x00000000);
	while (i < CELL_SIZE)
	{
		j = 1;
		while (j < CELL_SIZE)
		{
			mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_2d_map(t_game *gunstorm)
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
}

static void	map(void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	game_fps(gunstorm);
	draw_2d_map(gunstorm);
	ray_cast(map_width(gunstorm->map) * CELL_SIZE, gunstorm, true);
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
