/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_identifiers_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/22 02:44:11 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm_bonus.h"

static void	check_unknown(t_game *gunstorm, char *map, int index)
{
	while (map[index]
		&& map[index] != '\n'
		&& (map[index] == ' ' || map[index] == '\t'))
		index++;
	if (map[index] == '\n' || !map[index])
		return ;
	free(gunstorm);
	ft_putstr_fd(RED"Error\n", 2);
	ft_putstr_fd("Unknown identifier '", 2);
	while (map[index] && map[index] != '\n')
		ft_putchar_fd(map[index++], 2);
	ft_putstr_fd("'\n"RESET, 2);
	free(map);
	exit(EXIT_FAILURE);
}

static void	check_texture(t_game *gunstorm,
	char *map, char *id, bool *key_flag)
{
	if (*key_flag)
	{
		free(map);
		free(gunstorm);
		puterror(RED"Error\n",
			"Duplicated texture identifier '", id, "'\n"RESET);
		exit(EXIT_FAILURE);
	}
	*key_flag = true;
}

static void	check_duplicated(char *map, int index, t_game *gunstorm)
{
	static t_identifiers	keys;

	if (!ft_strncmp(map + index, "NO", 2))
		check_texture(gunstorm, map, "NO", &keys.no);
	else if (!ft_strncmp(map + index, "SO", 2))
		check_texture(gunstorm, map, "SO", &keys.so);
	else if (!ft_strncmp(map + index, "EA", 2))
		check_texture(gunstorm, map, "EA", &keys.ea);
	else if (!ft_strncmp(map + index, "WE", 2))
		check_texture(gunstorm, map, "WE", &keys.we);
	else if (!ft_strncmp(map + index, "F", 1))
		check_color(gunstorm, map, "F", &keys.f);
	else if (!ft_strncmp(map + index, "C", 1))
		check_color(gunstorm, map, "C", &keys.c);
	else if (check_line(map, index) == -1)
		check_unknown(gunstorm, map, index);
}

static void	validate_line(char *map, int index, t_game *gunstorm)
{
	while (map[index]
		&& (map[index] == ' ' || map[index] == '\t'))
		index++;
	check_duplicated(map, index, gunstorm);
}

void	validate_identifiers(char *map, t_game *gunstorm)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '\n')
			if (check_line(map, i + 1) != -1)
				break ;
		if (i == 0)
			validate_line(map, i, gunstorm);
		if (map[i] == '\n')
			validate_line(map, i + 1, gunstorm);
		i++;
	}
}
