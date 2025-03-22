/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniaudio_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:58:07 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/18 21:58:11 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// miniaudio_types.h
#ifndef MINIAUDIO_TYPES_H
# define MINIAUDIO_TYPES_H

# include "../../Sound/miniaudio.h"

typedef struct s_sound_data
{
	ma_result			result;
	ma_decoder			*decoder;
	ma_device_config	*device_config;
	ma_device			*device;
}						t_sound;

#endif
