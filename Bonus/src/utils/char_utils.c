/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:09:40 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/16 20:52:32 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

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
		|| a == 'S'
		|| a == 'D');
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
		|| a == 'S' || a == 'D');
}

bool	door_in_map(t_map map)
{
	int	x;
	int	y;

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
