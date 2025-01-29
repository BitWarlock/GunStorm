/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/29 15:11:42 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

char	*get_color_line(char *map)
{
	int		i;
	int		comma;
	char	*line;

	i = 0;
	comma = 0;
	while (map[i] && map[i] != '\n')
		i++;
	line = ft_substr(map, 0, i);
	i = -1;
	while (line[++i])
		if (line[i] == ',')
			comma++;
	if (comma == 2)
		return (line);
	return (free(line), NULL);
}

void	check_color(t_game *gunstorm,
	char *map, char *id, bool *key_flag)
{
	if (*key_flag)
	{
		free(map);
		free(gunstorm);
		puterror(RED"Error\n",
			"Duplicated color identifier '", id, "'\n"RESET);
		ft_putstr_fd("'\n"RESET, 2);
		exit(EXIT_FAILURE);
	}
	*key_flag = true;
}

int	get_cell_color(char cell)
{
	if (cell == '0' || player_char(cell))
		return (0x000000FF);
	if (cell == '1')
		return (0x898989FF);
	if (cell == 'D')
		return (0x62090bcc);
	return (0xfb8d90cc);
}
