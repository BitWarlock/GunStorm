/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/22 16:11:35 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

void	puterror(char *prefix, char *err1, char *err2, char *suffix)
{
	if (prefix)
		ft_putstr_fd(prefix, 2);
	if (err1)
		ft_putstr_fd(err1, 2);
	if (err2)
		ft_putstr_fd(err2, 2);
	if (suffix)
		ft_putstr_fd(suffix, 2);
}

void	texture_error(char *error)
{
	puterror(RED"Error\n", error,
		" texture file either missing or invalid\n"RESET, NULL);
	exit(EXIT_FAILURE);
}

void	fatal_error(char *error, char *msg)
{
	ft_putstr_fd(RED"Error\n", 2);
	if (!msg)
		puterror(error, "\n"RESET, NULL, NULL);
	else
		puterror(error, ": ", msg, "\n"RESET);
	exit(EXIT_FAILURE);
}

void	map_error(char *error_msg, t_game *gunstorm, char *map)
{
	free_game(gunstorm);
	free(map);
	puterror(RED"Error\n", "Map error: ", error_msg, "\n"RESET);
	exit(EXIT_FAILURE);
}

void	map_error_split(char *error_msg, t_game *gunstorm, char *map)
{
	free_split(gunstorm->map.rows);
	map_error(error_msg, gunstorm, map);
}
