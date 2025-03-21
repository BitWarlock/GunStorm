/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:04:03 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/21 03:25:08 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void	game_menu(t_game *gunstorm)
{
	gunstorm->mlx_data.door_msg->enabled = false;
	menu(gunstorm);
	if (gunstorm->menu)
		display_menu(gunstorm);
}

static void	game_state(t_game *gunstorm)
{
	gun_up(gunstorm);
	update_player_anim(gunstorm, &gunstorm->player_anim);
	mlx_set_cursor_mode(gunstorm->mlx_data.mlx, MLX_MOUSE_HIDDEN);
	gunstorm->mlx_data.menu->enabled = false;
	gunstorm->mlx_data.circle->enabled = true;
	if (gunstorm->game_has_doors && is_infront_door(gunstorm->map, gunstorm))
		gunstorm->mlx_data.door_msg->enabled = true;
}

static void	game_player_actions(t_game *gunstorm)
{
	mouse_rotate_pov(gunstorm, gunstorm->mlx_data.mlx->delta_time);
	player_movement(gunstorm, &gunstorm->player);
	game_fps(gunstorm);
}

static void	game_render(t_game *gunstorm)
{
	threaded_render(gunstorm, draw_floor);
	threaded_render(gunstorm, draw_sky);
	threaded_render(gunstorm, ray_caster);
	minimap(gunstorm);
}

void	game_loop(void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	if (!gunstorm->start_game)
		return ;
	game_menu(gunstorm);
	if (gunstorm->menu)
		return ;
	game_state(gunstorm);
	game_player_actions(gunstorm);
	game_render(gunstorm);
}
