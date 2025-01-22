/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/22 17:20:05 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/gunstorm.h"

static void	update_player_coord(t_player *player)
{
	player->position.x *= CELL_SIZE;
	player->position.y *= CELL_SIZE;
	player->position.x += (float)CELL_SIZE / 2;
	player->position.y += (float)CELL_SIZE / 2;
}

static void	game_init(t_game *gunstorm)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "GunStorm", true);
	if (!mlx)
		(free_all(gunstorm)), exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		(free_all(gunstorm)), mlx_terminate(mlx),
			exit(EXIT_FAILURE);
	gunstorm->mlx_data.mlx = mlx;
	gunstorm->mlx_data.img = img;
	gunstorm->start_time = mlx_get_time();
	gunstorm->frames = 0;
}

static void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	if (ydelta < 0)
		gunstorm->player.angle -= 0.1;
	if (ydelta > 0)
		gunstorm->player.angle += 0.1;
}

static void	game_start(t_game *gunstorm)
{
	game_init(gunstorm);
	mlx_loop_hook(gunstorm->mlx_data.mlx, game_loop, gunstorm);
	mlx_key_hook(gunstorm->mlx_data.mlx, game_hooks, gunstorm);
	mlx_scroll_hook(gunstorm->mlx_data.mlx, scroll_hook, gunstorm);
	mlx_loop(gunstorm->mlx_data.mlx);
	mlx_terminate(gunstorm->mlx_data.mlx);
}

void	game_core(char *map_file)
{
	t_game	*gunstorm;

	gunstorm = malloc(sizeof(t_game));
	if (!gunstorm)
		fatal_error("malloc", strerror(errno));
	input_parsing(map_file, gunstorm);
	update_player_coord(&gunstorm->player);
	game_start(gunstorm);
	free_all(gunstorm);
}
