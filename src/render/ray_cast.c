/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:51:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/22 17:20:32 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void	ray_init_direction(t_raycaster *ray,
							float start_angle, int x, int w)
{
	ray->ray_angle = start_angle + (FOV * x / w);
	ray->ray_dirx = cos(ray->ray_angle);
	ray->ray_diry = sin(ray->ray_angle);
	if (ray->ray_dirx == 0)
		ray->delta_distx = 1e30;
	else
		ray->delta_distx = fabs(1.0 / ray->ray_dirx);
	if (ray->ray_diry == 0)
		ray->delta_disty = 1e30;
	else
		ray->delta_disty = fabs(1.0 / ray->ray_diry);
}

static void	ray_init_steps(t_game *gunstorm, t_raycaster *ray)
{
	ray->player_x = gunstorm->player.position.x / CELL_SIZE;
	ray->player_y = gunstorm->player.position.y / CELL_SIZE;
	ray->map_x = (int)ray->player_x;
	ray->map_y = (int)ray->player_y;
	if (ray->ray_dirx < 0)
	{
		ray->step_x = -1;
		ray->side_distx = (ray->player_x - ray->map_x) * ray->delta_distx;
	}
	else
	{
		ray->step_x = 1;
		ray->side_distx = (ray->map_x + 1.0 - ray->player_x) * ray->delta_distx;
	}
	if (ray->ray_diry < 0)
	{
		ray->step_y = -1;
		ray->side_disty = (ray->player_y - ray->map_y) * ray->delta_disty;
	}
	else
	{
		ray->step_y = 1;
		ray->side_disty = (ray->map_y + 1.0 - ray->player_y) * ray->delta_disty;
	}
}

static mlx_texture_t	*ray_get_texture(t_game *gunstorm)
{
	if (gunstorm->ray.side == 0)
	{
		if (gunstorm->ray.step_x < 0)
			return (gunstorm->texture.west);
		return (gunstorm->texture.east);
	}
	if (gunstorm->ray.step_y < 0)
		return (gunstorm->texture.north);
	return (gunstorm->texture.south);
}

static void	ray_render(t_game *gunstorm, bool map_2d, int x)
{
	if (map_2d)
		ray_draw_line(gunstorm, gunstorm->mlx_data.img,
			gunstorm->player.position.x, gunstorm->player.position.y);
	else
		ray_draw_column(gunstorm, &gunstorm->ray,
			x, ray_get_texture(gunstorm));
}

void	ray_cast(int width, t_game *gunstorm, bool map_2d)
{
	float	start_angle;
	int		x;

	x = 0;
	start_angle = gunstorm->player.angle - HALF_FOV;
	while (x < width)
	{
		ray_init_direction(&gunstorm->ray, start_angle, x, width);
		ray_init_steps(gunstorm, &gunstorm->ray);
		ray_cast_dda(gunstorm, &gunstorm->ray);
		ray_render(gunstorm, map_2d, x);
		x++;
	}
}
