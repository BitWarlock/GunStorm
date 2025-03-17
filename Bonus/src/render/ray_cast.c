/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:51:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/17 02:40:52 by mrezki           ###   ########.fr       */
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

static mlx_texture_t	*ray_get_texture(t_game *gunstorm, t_raycaster ray)
{
	if (gunstorm->map.rows[ray.map_y]
		[ray.map_x] == 'D')
		return (gunstorm->texture.door);
	if (ray.side == 0)
	{
		if (ray.step_x < 0)
			return (gunstorm->texture.west);
		return (gunstorm->texture.east);
	}
	if (ray.step_y < 0)
		return (gunstorm->texture.north);
	return (gunstorm->texture.south);
}

void	*ray_caster(void *arg)
{
	t_thread	*thread;
	t_game		*gunstorm;
	float		start_angle;
	int			x;

	thread = (t_thread *)arg;
	x = thread->start;
	gunstorm = thread->gunstorm;
	start_angle = gunstorm->player.angle - HALF_FOV;
	while (x < thread->end)
	{
		ray_init_direction(&gunstorm->ray[thread->index],
			start_angle, x, WIDTH);
		ray_init_steps(gunstorm, &gunstorm->ray[thread->index]);
		ray_cast_dda(gunstorm, &gunstorm->ray[thread->index]);
		ray_render(gunstorm, &gunstorm->ray[thread->index],
			x, ray_get_texture(gunstorm, gunstorm->ray[thread->index]));
		x++;
	}
	return (NULL);
}

void	threaded_raycast(t_game *gunstorm, void *(*func) (void *))
{
	int			step;
	int			i;
	t_thread	raycast[THREADS];
	pthread_t	threads[THREADS];

	i = 0;
	step = WIDTH / THREADS;
	while (i < THREADS)
	{
		raycast[i].start = step * i;
		raycast[i].end = step * (i + 1);
		raycast[i].gunstorm = gunstorm;
		raycast[i].index = i;
		pthread_create(&threads[i], NULL, func, &raycast[i]);
		i++;
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
}
