/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:09:40 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/13 11:09:42 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gunstorm.h"

bool	player_char(char a)
{
	return (a == 'E'
		|| a == 'S' || a == 'W'
		|| a == 'N');
}

bool	valid_map_char(char a)
{
	return (a == ' ' || a == '1'
		|| a == '0' || a == 'E'
		|| a == 'W' || a == 'N'
		|| a == 'S');
}

bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	valid_char(char a)
{
	return (a == '1'
		|| a == '0' || a == 'E'
		|| a == 'W' || a == 'N'
		|| a == 'S');
}
