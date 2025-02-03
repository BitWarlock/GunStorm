/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_dda.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:24:00 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/22 17:20:32 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void	ray_update_h_intersect(t_raycaster *ray)
{
	if (ray->step_y > 0)
		ray->wall_y = ray->map_y + 1.0;
	else
		ray->wall_y = ray->map_y;
	ray->wall_x = ray->player_x + (ray->wall_y - ray->player_y)
		* ray->ray_dirx / ray->ray_diry;
	ray->side_disty += ray->delta_disty;
	ray->map_y += ray->step_y;
	ray->side = 1;
}

static void	ray_update_v_intersect(t_raycaster *ray)
{
	if (ray->step_x > 0)
		ray->wall_x = ray->map_x + 1.0;
	else
		ray->wall_x = ray->map_x;
	ray->wall_y = ray->player_y + (ray->wall_x - ray->player_x)
		* ray->ray_diry / ray->ray_dirx;
	ray->side_distx += ray->delta_distx;
	ray->map_x += ray->step_x;
	ray->side = 0;
}

static void	ray_check_collision(t_raycaster *ray,
								t_map world_map, int *hit_wall)
{
	if (!(ray->map_x >= 0 && ray->map_x < map_width(world_map)
			&& ray->map_y >= 0 && ray->map_y < world_map.height))
		return ;
	if (world_map.rows[ray->map_y][ray->map_x] == '1')
		*hit_wall = 1;
}

void	ray_cast_dda(t_game *gunstorm, t_raycaster *ray)
{
	int	hit_wall;

	hit_wall = 0;
	ray->wall_x = ray->player_x;
	ray->wall_y = ray->player_y;
	while (!hit_wall)
	{
		if (ray->side_distx < ray->side_disty)
			ray_update_v_intersect(ray);
		else
			ray_update_h_intersect(ray);
		ray_check_collision(ray, gunstorm->map, &hit_wall);
	}
}
