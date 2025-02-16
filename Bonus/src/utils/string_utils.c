/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/16 20:43:36 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

int	find(char *str, char *substr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str + i, substr, ft_strlen(substr)))
			return (i);
		i++;
	}
	return (-1);
}

bool	empty_line(char *line, int s)
{
	while (line[s] && line[s] != '\n')
	{
		if (line[s] != ' ')
			return (false);
		s++;
	}
	return (true);
}

int	check_line(char *line, int s)
{
	int	i;

	if (empty_line(line, s))
		return (-1);
	i = s;
	while (line[i] && line[i] != '\n')
	{
		if (!valid_map_char(line[i]))
			return (-1);
		i++;
	}
	return (s);
}

size_t	map_width(t_map map)
{
	size_t	width;
	int		i;

	width = 0;
	i = 0;
	while (i < map.height)
	{
		if (ft_strlen(map.rows[i]) > width)
			width = ft_strlen(map.rows[i]);
		i++;
	}
	return (width);
}

void	blocked_areas_warning(void)
{
	static int	count;

	if (count != 0)
		return ;
	count++;
	printf(MAG"Warning: Certain areas are"
		" inaccessible to the player\n"RESET);
}
