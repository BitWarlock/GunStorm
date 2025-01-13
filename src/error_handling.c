/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/13 11:10:02 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gunstorm.h"

void	texture_error(char *error)
{
	ft_printf(2, RED"Error\n");
	ft_printf(2, "%s texture file either missing or invalid\n"RESET, error);
	exit(EXIT_FAILURE);
}

void	fatal_error(char *error, char *msg)
{
	ft_printf(2, RED"Error\n");
	if (!msg)
		ft_printf(2, "%s\n"RESET, error);
	else
		ft_printf(2, "%s: %s\n"RESET, error, msg);
	exit(EXIT_FAILURE);
}

void	map_error(char *error_msg, t_game *gunstorm, char *map)
{
	free_game(gunstorm);
	free(map);
	ft_printf(2, RED"Error\n");
	ft_printf(2, "Map error: %s\n"RESET, error_msg);
	exit(EXIT_FAILURE);
}

void	map_error_split(char *error_msg, t_game *gunstorm, char *map)
{
	free_split(gunstorm->map.rows);
	map_error(error_msg, gunstorm, map);
}
