/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:42:54 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/17 21:11:37 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void	game_movement_hooks(mlx_key_data_t key, t_game *gunstorm)
{
	if (key.key == MLX_KEY_W)
		gunstorm->movement.forward
			= (key.action == MLX_PRESS || key.action == MLX_REPEAT);
	if (key.key == MLX_KEY_S)
		gunstorm->movement.backward
			= (key.action == MLX_PRESS || key.action == MLX_REPEAT);
	if (key.key == MLX_KEY_D)
		gunstorm->movement.right
			= (key.action == MLX_PRESS || key.action == MLX_REPEAT);
	if (key.key == MLX_KEY_A)
		gunstorm->movement.left
			= (key.action == MLX_PRESS || key.action == MLX_REPEAT);
}

void	update_angle(t_player *player)
{
	player->angle_degree = (int)(player->angle * 1800.0f / M_PI) % 3600;
	if (player->angle_degree < 0)
		player->angle_degree += 3600;
}

void	game_hooks(mlx_key_data_t key, void *param)
{
	t_game	*gunstorm;
	int		current_frame;

	gunstorm = (t_game *)param;
	gunstorm->start_game = true;
	mlx_delete_image(gunstorm->mlx_data.mlx, gunstorm->mlx_data.welcome_screen);
	game_movement_hooks(key, gunstorm);
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_ESCAPE))
	{
		current_frame = gunstorm->player_anim.current_frame;
		gunstorm->player_anim.frames[current_frame]->enabled = true;
		gunstorm->menu = !gunstorm->menu;
	}
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_LEFT))
		gunstorm->player.angle -= 0.1;
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_RIGHT))
		gunstorm->player.angle += 0.1;
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_E)
		&& is_infront_door(gunstorm->map, gunstorm))
		door_open_close(&gunstorm->map, gunstorm);
	update_angle(&gunstorm->player);
}
