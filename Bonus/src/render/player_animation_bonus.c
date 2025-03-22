/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:06:26 by agaladi           #+#    #+#             */
/*   Updated: 2025/03/22 03:48:58 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm_bonus.h"

void	game_init_animations(t_game *game, t_player_anim *anim)
{
	char	frame_path[128];
	int		i;

	i = 0;
	while (i < PLAYER_FRAME_COUNT)
	{
		sprintf(frame_path, "./assets/Gun/gun_frame_%d.png", i + 1);
		anim->textures[i] = mlx_load_png(frame_path);
		if (!anim->textures[i])
			(free_all(game)), fatal_error("MLX library failed", NULL);
		anim->frames[i] = mlx_texture_to_image(game->mlx_data.mlx,
				anim->textures[i]);
		mlx_delete_texture(anim->textures[i]);
		if (!anim->frames[i])
			(free_all(game)), fatal_error("MLX library failed", NULL);
		anim->frames[i]->enabled = false;
		mlx_image_to_window(game->mlx_data.mlx, anim->frames[i],
			game->player_anim.pos_x, game->player_anim.pos_y);
		anim->frames[i++]->instances[0].y = 680;
	}
	anim->current_frame = 0;
	anim->frames[0]->enabled = true;
}

void	update_player_anim(t_game *game, t_player_anim *anim)
{
	if (!anim->active || game->menu)
		return ;
	anim->frames[anim->current_frame]->enabled = false;
	anim->current_frame = (anim->current_frame + 1) % PLAYER_FRAME_COUNT;
	anim->frames[anim->current_frame]->enabled = true;
	anim->frames[anim->current_frame]->instances[0].y = 280;
	if (anim->current_frame == 0)
		anim->active = false;
}

void	gun_up(t_game *gunstorm)
{
	if (gunstorm->player_anim.current_frame == 0
		&& gunstorm->player_anim.frames[gunstorm->player_anim
			.current_frame]->instances[0].y > 280)
		gunstorm->player_anim.frames[gunstorm->player_anim
			.current_frame]->instances[0].y -= 10;
}

void	play_gunshot(t_gunsound *sound_system, t_sound *sound)
{
	if (!sound_system->sound_loaded
		|| ma_sound_is_playing(&sound_system->gunshot))
		return ;
	ma_device_set_master_volume(sound->device, 0.0);
	ma_sound_seek_to_pcm_frame(&sound_system->gunshot, 0);
	ma_sound_start(&sound_system->gunshot);
	ma_device_set_master_volume(sound->device, 0.7);
}

void	player_attack(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param)
{
	t_game	*game;

	(void)mods;
	game = (t_game *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		play_gunshot(&game->sound_system, &game->sound);
		game->player_anim.current_frame = 0;
		game->player_anim.active = true;
	}
}
