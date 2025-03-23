/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sky_floor_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 03:14:18 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/23 07:19:47 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm_bonus.h"

static int	rgba_color(t_rgb colors, int y, bool shine)
{
	float	brightness;
	float	distance_from_center;

	distance_from_center = fabsf((HEIGHT * 0.5f) - (float)y) / (HEIGHT * 0.5f);
	if (shine)
		return (colors.r << 24 | colors.g << 16
			| colors.b | 255);
	brightness = distance_from_center * 1.0;
	if (brightness < 0.2f)
		brightness = 0.2f;
	if (brightness > 1.0f)
		brightness = 1.0f;
	return (apply_brightness(colors, 255, brightness));
}

void	*draw_floor(void *arg)
{
	int			x;
	int			y;
	t_game		*gunstorm;
	t_thread	*thread;

	thread = (t_thread *)arg;
	gunstorm = thread->gunstorm;
	x = thread->start;
	while (x < thread->end)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y <= HEIGHT / 2)
				mlx_put_pixel(gunstorm->mlx_data.img, x, y,
					rgba_color(gunstorm->ceiling, y, gunstorm->brightness));
			else
				mlx_put_pixel(gunstorm->mlx_data.img, x, y,
					rgba_color(gunstorm->floor, y, gunstorm->brightness));
			y++;
		}
		x++;
	}
	return (NULL);
}

static int	get_pixel_color(mlx_texture_t *texture, int sky_x, int w_x, int w_y)
{
	int		position;
	int		y;
	int		x;
	uint8_t	*pixel;

	x = (w_x + sky_x) % texture->width;
	y = w_y * texture->height / (HEIGHT / 2);
	position = y * texture->width + x;
	position *= texture->bytes_per_pixel;
	pixel = &texture->pixels[position];
	return ((uint8_t)(pixel[0]) << 24
		| (uint8_t)(pixel[1]) << 16
		| (uint8_t)(pixel[2]) << 8 | pixel[3]);
}

void	*draw_sky(void *arg)
{
	t_thread	*thread;
	t_game		*gunstorm;
	int			x;
	int			y;
	uint32_t	color;

	thread = (t_thread *)arg;
	gunstorm = thread->gunstorm;
	x = thread->start;
	while (x < thread->end)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			color = get_pixel_color(gunstorm->texture.sky,
					(int)(gunstorm->texture.sky->width
						+ gunstorm->sky_offset), x, y);
			mlx_put_pixel(gunstorm->mlx_data.img, x, y, color);
			y++;
		}
		x++;
	}
	return (NULL);
}
