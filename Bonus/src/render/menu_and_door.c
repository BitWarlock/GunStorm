/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_and_door.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:04:03 by agaladi           #+#    #+#             */
/*   Updated: 2025/02/19 19:21:46 by mrezki           ###   ########.fr       */
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

static void	cell_infront_player(int *x, int *y, float angle)
{
	*x += (int)round(cos(angle));
	*y -= (int)round(sin(angle));
}

void	door_open_close(t_map *map, t_player player)
{
	int	x;
	int	y;

	x = floor(player.position.x / CELL_SIZE);
	y = floor(player.position.y / CELL_SIZE);
	cell_infront_player(&x, &y, player.angle);
	if (map->rows[y][x] == 'D')
		map->rows[y][x] = 'O';
	else if (map->rows[y][x] == 'O')
		map->rows[y][x] = 'D';
}

bool	is_infront_door(t_map map, t_player player)
{
	char	cell;
	int		x;
	int		y;

	x = floor(player.position.x / CELL_SIZE);
	y = floor(player.position.y / CELL_SIZE);
	cell_infront_player(&x, &y, player.angle);
	cell = map.rows[y][x];
	return (cell == 'D' || cell == 'O');
}
