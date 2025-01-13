/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:14 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/13 11:10:14 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gunstorm.h"

void	free_textures(char *map, t_game *gunstorm, int index)
{
	if (index >= 1)
		free(gunstorm->texture.north);
	if (index >= 2)
		free(gunstorm->texture.south);
	if (index >= 3)
		free(gunstorm->texture.west);
	free(gunstorm);
	free(map);
}

void	free_game(t_game *gunstorm)
{
	free(gunstorm->texture.north);
	free(gunstorm->texture.east);
	free(gunstorm->texture.south);
	free(gunstorm->texture.west);
	free(gunstorm);
}

void	free_split(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

void	free_all(t_game *gunstorm)
{
	free_split(gunstorm->map.rows);
	free_game(gunstorm);
}
