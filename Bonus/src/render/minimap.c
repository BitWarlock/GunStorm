/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:06:26 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/29 23:17:25 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void rotate_point(float *x, float *y, float angle) {
    float rad = angle * (M_PI / 180.0);
    float cos_theta = cos(rad), sin_theta = sin(rad);
    float x_new = *x * cos_theta - *y * sin_theta;
    float y_new = *x * sin_theta + *y * cos_theta;
    *x = x_new; *y = y_new;
}

// draw player
void draw_player_icon(mlx_image_t *img, t_pair pos, int length, float angle, uint32_t color) {
    float points[3][2] = {
        {0, -length},        // top point
        {-length / 2.0, length},  // bottom left point
        {length / 2.0, length}    // bottom right point
    };

    // Rotate and translate points
    for (int i = 0; i < 3; i++) {
        rotate_point(&points[i][0], &points[i][1], angle);
        points[i][0] += pos.x;
        points[i][1] += pos.y;
    }



    // Sort points by y-coordinate
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (points[j][1] > points[j + 1][1]) {
                float temp[2];
                memcpy(temp, points[j], sizeof(temp));
                memcpy(points[j], points[j + 1], sizeof(temp));
                memcpy(points[j + 1], temp, sizeof(temp));
            }
        }
    }

    // Linear interpolation for triangle fill
   for (float py = points[0][1]; py <= points[2][1]; py++) {
       if (py < 0 || py >= img->height) continue;

       float left_x, right_x;

       if (py < points[1][1]) {
           left_x = points[0][0] + (points[1][0] - points[0][0]) * (py - points[0][1]) / (points[1][1] - points[0][1]);
           right_x = points[0][0] + (points[2][0] - points[0][0]) * (py - points[0][1]) / (points[2][1] - points[0][1]);
       } else {
           left_x = points[1][0] + (points[2][0] - points[1][0]) * (py - points[1][1]) / (points[2][1] - points[1][1]);
           right_x = points[0][0] + (points[2][0] - points[0][0]) * (py - points[0][1]) / (points[2][1] - points[0][1]);
       }

       if (left_x > right_x) {
           float temp = left_x;
           left_x = right_x;
           right_x = temp;
       }

       left_x = fmax(0, fmin(left_x, img->width - 1));
       right_x = fmax(0, fmin(right_x, img->width - 1));

       for (int f = (int)left_x; f <= (int)right_x; f++) {
           mlx_put_pixel(img, f, (int)py, color);
       }
   }
}

static bool	is_within_circle(t_pair c, int px, int py)
{
	float	dist;

	dist = ((px - c.x) * (px - c.x)) + ((py - c.y) * (py - c.y));
	return (dist <= (CELL_SIZE * 3) * (CELL_SIZE * 3));
}

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

static void	draw_minimap_cell(t_game *gunstorm, int cx, int cy, char type)
{
	int		px;
	int		py;
	int		col;

	col = get_cell_color(type);
	px = 0;
	draw_player_icon(gunstorm->mlx_data.img, (t_pair){100, 100}, 10,(gunstorm->player.angle * 180) / M_PI + 90, 0x35deedcc);
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

void	minimap(t_game *gunstorm)
{
	int	cx;
	int	cy;
	int	cx_limit;
	int	cy_limit;

	cx = (gunstorm->player.position.x / CELL_SIZE) - 4;
	if (cx < 0)
		cx = 0;
	cx_limit = cx + 8;
	if (cx_limit >= map_width(gunstorm->map))
		cx_limit = map_width(gunstorm->map) - 1;
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
