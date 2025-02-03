/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:02 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/03 19:31:05 by agaladi          ###   ########.fr       */
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

void load_player_anim(t_game *game, t_player_anim *anim)
{
    char frame_path[128];  // Ensure the buffer is large enough

	
    for (int i = 0; i < PLAYER_FRAME_COUNT; i++)
    {
        // Construct the file path for each frame.
        // For example: "./light_saber/lightSaber_frame_0.png"
        sprintf(frame_path, "./Gun/gun_frame_%d.png", i+1);

        // Load the texture
        anim->textures[i] = mlx_load_png(frame_path);
        if (!anim->textures[i])
        {
            fprintf(stderr, "Failed to load texture: %s\n", frame_path);
            exit(EXIT_FAILURE);
        }

        // Create the image from the texture
        anim->frames[i] = mlx_texture_to_image(game->mlx_data.mlx, anim->textures[i]);
        if (!anim->frames[i])
        {
            fprintf(stderr, "Failed to create image for: %s\n", frame_path);
            exit(EXIT_FAILURE);
        }

        // Initially disable all frames
        anim->frames[i]->enabled = false;

        // Add the image to the window at the desired position.
        // You might want to use anim->pos_x and anim->pos_y if you want to store position.
        mlx_image_to_window(game->mlx_data.mlx, anim->frames[i], game->player_anim.pos_x, game->player_anim.pos_y);
    }

    // Start with the first frame enabled.
    anim->current_frame = 0;
    anim->frames[0]->enabled = true;
}


/*// keeps looping throu all frames*/
/*void update_player_anim(t_game *game, t_player_anim *anim)*/
/*{*/
/*    // Hide the current frame*/
/*    anim->frames[anim->current_frame]->enabled = false;*/
/**/
/*    // Advance to the next frame (wrapping around)*/
/*    anim->current_frame = (anim->current_frame + 1) % PLAYER_FRAME_COUNT;*/
/**/
/*    // Show the new frame*/
/*    anim->frames[anim->current_frame]->enabled = true;*/
/*}*/




void update_player_anim(t_game *game, t_player_anim *anim)
{
    if (!anim->active || anim->frames[anim->current_frame]->instances[0].y > 280)
        return;
    // Hide the current frame
    anim->frames[anim->current_frame]->enabled = false;

    // Advance to the next frame
    anim->current_frame = (anim->current_frame + 1) % PLAYER_FRAME_COUNT;

    // Show the new frame
    anim->frames[anim->current_frame]->enabled = true;

    // Stop animation after one full loop (optional)
    if (anim->current_frame == 0)
        anim->active = false;
}


static void	game_init_vars(t_game *gunstorm, mlx_t *mlx)
{
	mlx_texture_t	*tex;
	mlx_image_t		*circle;
	mlx_image_t		*menu;

	gunstorm->start_time = mlx_get_time();
	gunstorm->frames = 0;
	gunstorm->start_game = false;
	gunstorm->menu = false;
	gunstorm->player_anim.active = false;
	tex = mlx_load_png("./circle2.png");
	circle = mlx_texture_to_image(mlx, tex);
	mlx_resize_image(circle, 200, 200);
	mlx_delete_texture(tex);
	tex = mlx_load_png("./menu.png");
	menu = mlx_texture_to_image(mlx, tex);
	mlx_image_to_window(mlx, circle, 1, 1);
	gunstorm->mlx_data.circle = circle;
	gunstorm->mlx_data.menu = menu;
	mlx_image_to_window(mlx, menu, 0, 0);
	menu->enabled = false;
	// display player
	// Set the desired position for the player animation
	// for gun
	gunstorm->player_anim.pos_x = WIDTH / 3;
	gunstorm->player_anim.pos_y = 650;//280;
	// for light saber
    /*gunstorm->player_anim.pos_x = WIDTH / 3;*/
    /*gunstorm->player_anim.pos_y = 90;*/
    
    // Load the player animation frames
    load_player_anim(gunstorm, &gunstorm->player_anim);

	// hide/show mouse cursor
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	gunstorm->mlx_data.door_msg = mlx_put_string(gunstorm->mlx_data.mlx,
			"Press O to open/close the door", WIDTH / 2, 300);
	gunstorm->mlx_data.door_msg->enabled = false;
	gunstorm->mlx_data.circle->enabled = false;
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
	game_init_vars(gunstorm, mlx);
}


void player_attack(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
    t_game *game = (t_game *)param;

    if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)  // Adjust for your library's button/action enums
    {
        game->player_anim.active = true;  // Flag to start animation
    }
}

static void	game_start(t_game *gunstorm)
{
	mlx_texture_t	*welcome_tex;
	mlx_image_t		*welcome_screen;

	game_init(gunstorm);
	welcome_tex = mlx_load_png("./welcome.png");
	welcome_screen = mlx_texture_to_image(gunstorm->mlx_data.mlx, welcome_tex);
	mlx_image_to_window(gunstorm->mlx_data.mlx, welcome_screen, 0, 0);
	gunstorm->mlx_data.welcome_screen = welcome_screen;
	mlx_mouse_hook(gunstorm->mlx_data.mlx, player_attack, gunstorm);
	mlx_loop_hook(gunstorm->mlx_data.mlx, game_loop, gunstorm);
	mlx_key_hook(gunstorm->mlx_data.mlx, game_hooks, gunstorm);
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
