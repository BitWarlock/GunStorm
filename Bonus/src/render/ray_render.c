/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:27:11 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/27 22:48:06 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void	ray_wall_bounds(t_game *gunstorm, t_raycaster *ray)
{
	int		wall_height;
	float	perp_walldist;

	if (ray->side == 0)
		perp_walldist = ray->side_distx - ray->delta_distx;
	else
		perp_walldist = ray->side_disty - ray->delta_disty;
	perp_walldist *= cos(ray->ray_angle - gunstorm->player.angle);
	ray->perp_wall = perp_walldist;
	wall_height = (int)(HEIGHT / perp_walldist);
	ray->wall_height = wall_height;
	ray->wall_start = -wall_height / 2 + HEIGHT / 2;
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = wall_height / 2 + HEIGHT / 2;
	if (ray->wall_end >= HEIGHT)
		ray->wall_end = HEIGHT - 1;
}

static int	texture_pixel_color(mlx_texture_t *texture, int x, int y)
{
	int		position;
	uint8_t	*pixel;

	if (x < 0 || x >= texture->width
		|| y < 0 || y >= texture->height)
		return (0);
	position = y * texture->width + x;
	position *= texture->bytes_per_pixel;
	pixel = &texture->pixels[position];
	return (pixel[0] << 24 | pixel[1] << 16
		| pixel[2] << 8 | pixel[3]);
}

static void	ray_texture_coords(t_raycaster *ray, mlx_texture_t *texture)
{
	int		texture_x;
	float	texture_step;
	float	wall_x;

	if (ray->side == 0)
		wall_x = ray->wall_y - ray->map_y;
	else
		wall_x = ray->wall_x - ray->map_x;
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * texture->width);
	if ((ray->side == 0 && ray->ray_dirx > 0)
		|| (ray->side == 1 && ray->ray_diry < 0))
		texture_x = texture->width - texture_x - 1;
	ray->texture_x = texture_x;
	ray->texture_step = texture->height / ray->wall_height;
	ray->texture_pos = (ray->wall_start - (float)HEIGHT / 2
			+ ray->wall_height / 2) * ray->texture_step;
}

void	ray_draw_column(t_game *gunstorm, t_raycaster *ray,
						int x, mlx_texture_t *texture)
{
	int	texture_y;
	int	y;

	ray_wall_bounds(gunstorm, ray);
	ray_texture_coords(ray, texture);
	y = ray->wall_start;
	while (y < ray->wall_end)
	{
		texture_y = (int)ray->texture_pos;
		if (texture_y < 0)
			texture_y = 0;
		if (texture_y >= texture->height)
			texture_y = texture->height - 1;
		ray->texture_pos += ray->texture_step;
		mlx_put_pixel(gunstorm->mlx_data.img, x, y,
			texture_pixel_color(texture, ray->texture_x, texture_y));
		y++;
	}
}

void	ray_draw_wall(t_game *gunstorm, t_raycaster ray, int x)
{
	int	wall_color;
	int	i;

	ray_wall_bounds(gunstorm, &ray);
	wall_color = 0x036244cc;
	if (ray.side == 1)
		wall_color /= 2;
	i = ray.wall_start;
	while (i < ray.wall_end)
	{
		mlx_put_pixel(gunstorm->mlx_data.img, x, i, wall_color);
		i++;
	}
}
