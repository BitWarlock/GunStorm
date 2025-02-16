/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_and_door.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:04:03 by agaladi           #+#    #+#             */
/*   Updated: 2025/02/16 20:30:35 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

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

	if (gunstorm->menu
		&& mlx_is_mouse_down(gunstorm->mlx_data.mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(gunstorm->mlx_data.mlx, &x, &y);
		if (x >= 600 && x <= 1400 && y >= 610 && y <= 730)
			gunstorm->menu = false;
		if (x >= 600 && x <= 1400 && y >= 770 && y <= 890)
			mlx_close_window(gunstorm->mlx_data.mlx);
	}
}

void	door_open_close(t_map *map, t_pair player)
{
	int	x;
	int	y;

	x = floor(player.x / CELL_SIZE);
	y = floor(player.y / CELL_SIZE);
	if (map->rows[y - 1][x] == 'D')
		map->rows[y - 1][x] = 'O';
	else if (map->rows[y + 1][x] == 'D')
		map->rows[y + 1][x] = 'O';
	else if (map->rows[y][x + 1] == 'D')
		map->rows[y][x + 1] = 'O';
	else if (map->rows[y][x - 1] == 'D')
		map->rows[y][x - 1] = 'O';
	else if (map->rows[y - 1][x] == 'O')
		map->rows[y - 1][x] = 'D';
	else if (map->rows[y + 1][x] == 'O')
		map->rows[y + 1][x] = 'D';
	else if (map->rows[y][x + 1] == 'O')
		map->rows[y][x + 1] = 'D';
	else if (map->rows[y][x - 1] == 'O')
		map->rows[y][x - 1] = 'D';
}
