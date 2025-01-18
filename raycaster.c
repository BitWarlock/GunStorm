/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:51:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/18 18:25:02 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/gunstorm.h"

void	ray_direction(t_raycaster *ray, float start_angle, int x, int w)
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

void	ray_steps(t_game *gunstorm, t_raycaster *ray)
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

void	update_horizontal_side(t_raycaster *ray)
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

void	update_vertical_side(t_raycaster *ray)
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

void	ray_hit_wall(t_raycaster *ray, t_map world_map, int *hit_wall)
{
	if (!(ray->map_x >= 0 && ray->map_x < map_width(world_map)
			&& ray->map_y >= 0 && ray->map_y < world_map.height))
		return ;
	if (world_map.rows[ray->map_y][ray->map_x] == '1')
		*hit_wall = 1;
}

void	perform_dda(t_game *gunstorm, t_raycaster *ray)
{
	int	hit_wall;

	hit_wall = 0;
	ray->wall_x = ray->player_x;
	ray->wall_y = ray->player_y;
	while (!hit_wall)
	{
		if (ray->side_distx < ray->side_disty)
			update_vertical_side(ray);
		else
			update_horizontal_side(ray);
		ray_hit_wall(ray, gunstorm->map, &hit_wall);
	}
}

void	draw_line(t_game *gunstorm, mlx_image_t *img)
{
	int		i;
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	step;

	dx = gunstorm->ray.wall_x * CELL_SIZE - gunstorm->player.position.x;
	dy = gunstorm->ray.wall_y * CELL_SIZE - gunstorm->player.position.y;
	step = fmax(fabs(dx), fabs(dy));
	dx /= step;
	dy /= step;
	x = gunstorm->player.position.x;
	y = gunstorm->player.position.y;
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

void	wall_start_end(t_game *gunstorm, t_raycaster ray,
				int *wall_start, int *wall_end)
{
	int		wall_height;
	float	perp_walldist;

	if (ray.side == 0)
		perp_walldist = ray.side_distx - ray.delta_distx;
	else
		perp_walldist = ray.side_disty - ray.delta_disty;
	perp_walldist *= cos(ray.ray_angle - gunstorm->player.angle);
	wall_height = (int)(HEIGHT / perp_walldist);
	*wall_start = -wall_height / 2 + HEIGHT / 2;
	if (*wall_start < 0)
		*wall_start = 0;
	*wall_end = wall_height / 2 + HEIGHT / 2;
	if (*wall_end >= HEIGHT)
		*wall_end = HEIGHT - 1;
}

void	draw_wall(t_game *gunstorm, t_raycaster ray, int x)
{
	int	wall_start;
	int	wall_end;
	int	wall_color;
	int	i;

	wall_start_end(gunstorm, ray, &wall_start, &wall_end);
	wall_color = 0x036244cc;
	if (ray.side == 1)
		wall_color /= 2;
	i = wall_start;
	while (i < wall_end)
	{
		mlx_put_pixel(gunstorm->mlx_data.img, x, i, wall_color);
		i++;
	}
}

void	raycaster(int width, t_game *gunstorm, bool map_2d)
{
	float	start_angle;
	int		x;

	x = 0;
	start_angle = gunstorm->player.angle - HALF_FOV;
	while (x < width)
	{
		ray_direction(&gunstorm->ray, start_angle, x, width);
		ray_steps(gunstorm, &gunstorm->ray);
		perform_dda(gunstorm, &gunstorm->ray);
		if (map_2d)
			draw_line(gunstorm, gunstorm->mlx_data.img);
		else
			draw_wall(gunstorm, gunstorm->ray, x);
		x++;
	}
}
