/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:38:21 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/18 22:00:13 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"
#include "../../../Sound/miniaudio.h"

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

void	sound_error(t_game *gunstorm)
{
	free(gunstorm->sound.device);
	free(gunstorm->sound.device_config);
	free(gunstorm->sound.decoder);
	free_all(gunstorm);
	puterror(RED"Error\n", "Game sound error", NULL, RESET"\n");
	exit(EXIT_FAILURE);
}

void	data_callback(ma_device *pDevice, void *pOutput,
			const void *pInput, ma_uint32 frameCount)
{
	ma_decoder	*p_decoder;

	p_decoder = (ma_decoder *)pDevice->pUserData;
	if (p_decoder == NULL)
		return ;
	ma_data_source_read_pcm_frames(p_decoder, pOutput, frameCount, NULL);
	(void)pInput;
}

void	sound_devices_init(ma_decoder *decoder,
			ma_device_config *device_config, t_game *gunstorm)
{
	*device_config = ma_device_config_init(ma_device_type_playback);
	device_config->playback.format = decoder->outputFormat;
	device_config->playback.channels = decoder->outputChannels;
	device_config->sampleRate = decoder->outputSampleRate;
	device_config->dataCallback = data_callback;
	device_config->pUserData = decoder;
	if (ma_device_init(NULL, device_config,
			gunstorm->sound.device) != MA_SUCCESS)
		(ma_decoder_uninit(decoder)), sound_error(gunstorm);
	if (ma_device_start(gunstorm->sound.device) != MA_SUCCESS)
		(ma_device_uninit(gunstorm->sound.device)),
			ma_decoder_uninit(decoder), sound_error(gunstorm);
	ma_device_set_master_volume(gunstorm->sound.device, 0.6);
}

void	game_sound_init(t_game *gunstorm, t_sound *sound)
{
	sound->decoder = malloc(sizeof(ma_decoder));
	sound->device_config = malloc(sizeof(ma_device_config));
	sound->device = malloc(sizeof(ma_device));
	if (!sound->decoder || !sound->device_config
		|| !sound->device)
		sound_error(gunstorm);
	sound->result = ma_decoder_init_file("../Sound/soundtrack.mp3",
			NULL, sound->decoder);
	if (sound->result != MA_SUCCESS)
		sound_error(gunstorm);
	ma_data_source_set_looping(sound->decoder, MA_TRUE);
	sound_devices_init(sound->decoder, sound->device_config, gunstorm);
}
