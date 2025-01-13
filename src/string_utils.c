/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/13 11:10:14 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gunstorm.h"

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
