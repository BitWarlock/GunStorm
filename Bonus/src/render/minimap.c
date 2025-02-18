/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:06:26 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/18 18:46:57 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void	put_pixel_in_circle(t_game *gunstorm, int px, int py, int col)
{
	float	mx;
	float	my;
	int		i;
	int		j;

	if (is_within_circle(gunstorm->player.position, px, py))
	{
		mx = 100
			+ (px - gunstorm->player.position.x) * 3;
		my = 100
			+ (py - gunstorm->player.position.y) * 3;
		i = 0;
		while (i < 5)
		{
			j = -1;
			while (++j < 5)
				mlx_put_pixel(gunstorm->mlx_data.img, mx + j, my + i, col);
			i++;
		}
	}
}

// Main function to draw the player icon
void	draw_player_icon(mlx_image_t *img, t_pair pos, int length, float angle)
{
	t_pair	points[3];

	points[0].x = 0;
	points[0].y = -length;
	points[1].x = -length / 2.0;
	points[1].y = length;
	points[2].x = length / 2.0;
	points[2].y = length;
	rotate_and_translate_points(points, pos, angle);
	sort_points_by_y(points);
	fill_triangle(img, points, 0x35deedcc);
}

static void	draw_minimap_cell(t_game *gunstorm, int cx, int cy, char type)
{
	int		px;
	int		py;
	int		col;

	col = get_cell_color(type);
	px = 0;
	draw_player_icon(gunstorm->mlx_data.img, (t_pair){100, 100}, 10,
		(gunstorm->player.angle * 180) / M_PI + 90);
	while (px < CELL_SIZE)
	{
		py = 0;
		while (py < CELL_SIZE)
		{
			put_pixel_in_circle(gunstorm, cx + px, cy + py, col);
			py++;
		}
		px++;
	}
}

static void	x_init(t_game *gunstorm, int *cx, int *cx_limit)
{
	*cx = (gunstorm->player.position.x / CELL_SIZE) - 4;
	if (*cx < 0)
		*cx = 0;
	*cx_limit = *cx + 8;
	if (*cx_limit >= map_width(gunstorm->map))
		*cx_limit = map_width(gunstorm->map) - 1;
}

void	minimap(t_game *gunstorm)
{
	int	cx;
	int	cy;
	int	cx_limit;
	int	cy_limit;

	x_init(gunstorm, &cx, &cx_limit);
	while (cx <= cx_limit)
	{
		cy = (gunstorm->player.position.y / CELL_SIZE) - 4;
		if (cy < 0)
			cy = 0;
		cy_limit = cy + 8;
		if (cy_limit >= gunstorm->map.height)
			cy_limit = gunstorm->map.height - 1;
		while (cy <= cy_limit)
		{
			draw_minimap_cell(gunstorm, cx * CELL_SIZE, cy * CELL_SIZE,
				gunstorm->map.rows[cy][cx]);
			cy++;
		}
		cx++;
	}
}
