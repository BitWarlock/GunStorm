/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/13 11:10:02 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gunstorm.h"

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
		ft_printf(2, RED"Error\n");
		ft_printf(2, "Duplicated color identifier '%s'\n"RESET, id);
		exit(EXIT_FAILURE);
	}
	*key_flag = true;
}
