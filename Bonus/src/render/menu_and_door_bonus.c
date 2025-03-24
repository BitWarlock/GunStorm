/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_and_door_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:04:03 by agaladi           #+#    #+#             */
/*   Updated: 2025/03/24 03:20:51 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm_bonus.h"

void	display_menu(t_game *gunstorm)
{
	gunstorm->player_anim.frames[gunstorm->player_anim.current_frame]
		->enabled = false;
	gunstorm->mlx_data.circle->enabled = false;
	gunstorm->mlx_data.menu->enabled = true;
	mlx_set_cursor_mode(gunstorm->mlx_data.mlx, MLX_MOUSE_NORMAL);
}

void	menu(t_game *gunstorm)
{
	int	x;
	int	y;

	if (gunstorm->menu && mlx_is_mouse_down(gunstorm->mlx_data.mlx,
			MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(gunstorm->mlx_data.mlx, &x, &y);
		if (x >= 710 && x <= 1200 && y >= 600 && y <= 780)
			gunstorm->menu = false;
		if (x >= 710 && x <= 1200 && y >= 830 && y <= 1000)
			mlx_close_window(gunstorm->mlx_data.mlx);
	}
}

bool	map_has_doors(t_map map)
{
	size_t	x;
	int		y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < ft_strlen(map.rows[y]))
		{
			if (map.rows[y][x] == 'D')
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

void	door_open_close(t_map *map, t_game *gunstorm)
{
	int	x;
	int	y;

	x = floor(gunstorm->player.position.x / CELL_SIZE);
	y = floor(gunstorm->player.position.y / CELL_SIZE);
	x += (int)round(gunstorm->cos_table[gunstorm->player.angle_degree]);
	y += (int)round(gunstorm->sin_table[gunstorm->player.angle_degree]);
	if (map->rows[y][x] == 'D')
		map->rows[y][x] = 'O';
	else if (map->rows[y][x] == 'O')
		map->rows[y][x] = 'D';
}

bool	is_infront_door(t_map map, t_game *gunstorm)
{
	char	cell;
	int		x;
	int		y;

	x = floor(gunstorm->player.position.x / CELL_SIZE);
	y = floor(gunstorm->player.position.y / CELL_SIZE);
	x += (int)round(gunstorm->cos_table[gunstorm->player.angle_degree]);
	y += (int)round(gunstorm->sin_table[gunstorm->player.angle_degree]);
	cell = map.rows[y][x];
	return (cell == 'D' || cell == 'O');
}
