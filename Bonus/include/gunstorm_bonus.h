/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gunstorm_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:29 by mrezki            #+#    #+#             */
/*   Updated: 2025/03/25 05:57:02 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUNSTORM_BONUS_H

# define GUNSTORM_BONUS_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../libft/libft.h"
# include "miniaudio_types_bonus.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MINIAUDIO_IMPLEMENTATION

# define WIDTH 1920
# define HEIGHT 1080
# define FOV 1.0471975511965976      /* 60 degrees, PI / 3 in radians */
# define HALF_FOV 0.5235987755982988 /* Half of POV. 30 degrees */
# define CELL_SIZE 8
# define SPEED 5.0
# define MAG "\e[0;35m"
# define RED "\e[0;31m"
# define RESET "\e[0m"
# define THREADS 8

typedef enum s_direction
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
}					t_direction;
# define PLAYER_FRAME_COUNT 18

// animation
typedef struct s_player_anim
{
	mlx_texture_t	*textures[PLAYER_FRAME_COUNT];
	mlx_image_t		*frames[PLAYER_FRAME_COUNT];
	int				current_frame;
	int				pos_x;
	int				pos_y;
	bool			active;
}					t_player_anim;

typedef struct s_identifiers
{
	bool			no;
	bool			so;
	bool			ea;
	bool			we;
	bool			f;
	bool			c;
}					t_identifiers;

typedef struct s_pair
{
	float			x;
	float			y;
}					t_pair;

typedef struct s_player
{
	t_pair			position;
	char			direction;
	float			angle;
	int				angle_degree;
}					t_player;

typedef struct s_map
{
	char			**rows;
	int				height;
}					t_map;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_texture_t	*door;
	mlx_texture_t	*sky;
}					t_texture;

typedef struct s_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*circle;
	mlx_image_t		*rotated;
	mlx_image_t		*menu;
	mlx_image_t		*door_msg;
	mlx_image_t		*welcome_screen;
	mlx_image_t		*player;
}					t_mlx;

typedef struct s_raycaster
{
	int				side;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				wall_end;
	int				wall_start;
	float			wall_x;
	float			wall_y;
	float			wall_height;
	float			perp_wall;
	float			player_x;
	float			player_y;
	float			ray_dirx;
	float			ray_diry;
	float			ray_angle;
	float			side_distx;
	float			side_disty;
	float			delta_distx;
	float			delta_disty;
	float			texture_x;
	float			texture_step;
	float			texture_pos;
}					t_raycaster;

typedef struct s_move
{
	bool			forward;
	bool			backward;
	bool			left;
	bool			right;
}					t_move;

typedef struct s_gunsound
{
	ma_engine		engine;
	ma_sound		gunshot;
	bool			sound_loaded;
}					t_gunsound;

typedef struct s_game
{
	mlx_image_t		*cell;
	t_texture		texture;
	t_player		player;
	t_rgb			floor;
	t_rgb			ceiling;
	t_map			map;
	t_mlx			mlx_data;
	t_player_anim	player_anim;
	t_raycaster		ray[THREADS];
	t_sound			sound;
	t_move			movement;
	t_gunsound		sound_system;
	float			ray_angle_step;
	float			rotation_speed;
	float			cos_table[3600];
	float			sin_table[3600];
	double			start_time;
	float			move_speed;
	bool			menu;
	bool			brightness;
	bool			start_game;
	bool			game_has_doors;
	int				frames;
	float			sky_offset;
}					t_game;

typedef struct s_thread
{
	t_game			*gunstorm;
	int				index;
	int				start;
	int				end;
}					t_thread;

// ======================
// GAME INITIALIZATION
// ======================

void				game_init_gunsound(t_gunsound *sound_system,
						t_game *gunstorm);
void				game_init_animations(t_game *game, t_player_anim *anim);
void				game_init_soundtrack(t_game *gunstorm, t_sound *sound);
void				game_init_lookup_t(t_game *gunstorm);
void				game_init(t_game *gunstorm);

// ======================
// GAME LOOP AND HOOKS
// ======================

void				player_attack(mouse_key_t button, action_t action,
						modifier_key_t mods, void *param);
void				mouse_rotate_pov(t_game *gunstorm, float delta_time);
void				game_hooks(mlx_key_data_t key, void *param);
void				game_fps(t_game *gunstorm);
void				game_loop(void *param);

// ======================
// PLAYER AND MOVEMENT
// ======================

void				update_player_anim(t_game *game, t_player_anim *anim);
void				player_movement(t_game *gunstorm, t_player *player);
void				update_angle(t_player *player);
void				gun_up(t_game *gunstorm);

// ======================
// RAYCASTING AND RENDERING
// ======================

void				ray_render(t_game *gunstorm, t_raycaster *ray, int x,
						mlx_texture_t *texture);
void				ray_draw_line(t_game *gunstorm, mlx_image_t *img, float x,
						float y);
void				threaded_render(t_game *gunstorm, void *(*func)(void *));
void				ray_draw_wall(t_game *gunstorm, t_raycaster ray, int x);
void				ray_wall_bounds(t_game *gunstorm, t_raycaster *ray);
void				ray_cast(int width, t_game *gunstorm, bool map_2d);
void				ray_cast_dda(t_game *gunstorm, t_raycaster *ray);
void				*draw_floor(void *arg);
void				*ray_caster(void *arg);
void				*draw_sky(void *arg);

// ======================
// MAP AND MINIMAP
// ======================

void				door_open_close(t_map *map, t_game *gunstorm);
bool				is_infront_door(t_map map, t_game *gunstorm);
void				minimap(t_game *gunstorm);
bool				map_has_doors(t_map map);
void				map_2d(t_game *gunstorm);
bool				door_in_map(t_map map);
size_t				map_width(t_map map);

// ======================
// GRAPHICS AND DRAWING
// ======================

void				draw_player_icon(mlx_image_t *img, t_pair pos, int length,
						float angle);
void				rotate_and_translate_points(t_pair points[3], t_pair pos,
						float angle);
void				fill_triangle(mlx_image_t *img, t_pair pts[3],
						uint32_t color);
int					apply_brightness(t_rgb colors, int alpha, float brightness);
bool				is_within_circle(t_pair c, int px, int py);
void				sort_points_by_y(t_pair points[3]);

// ======================
// SOUND AND AUDIO
// ======================

void				play_gunshot(t_gunsound *sound_system, t_sound *sound);
void				sound_error(t_game *gunstorm);
void				free_sound(t_game *gunstorm);

// ======================
// MENU AND UI
// ======================

void				print_gunstorm(t_game *gunstorm);
void				display_menu(t_game *gunstorm);
void				menu(t_game *gunstorm);

// ======================
// ERROR HANDLING
// ======================

void				map_error_split(char *error_msg, t_game *gunstorm,
						char *map);
void				puterror(char *prefix, char *err1, char *err2,
						char *suffix);
void				map_error(char *error_msg, t_game *gunstorm, char *map);
void				fatal_error(char *error, char *msg);
void				blocked_areas_warning(void);
void				texture_error(char *error);

// ======================
// MEMORY MANAGEMENT
// ======================

void				free_textures(char *map, t_game *gunstorm, int index);
void				free_game(t_game *gunstorm);
void				free_all(t_game *gunstorm);
void				free_split(char **strs);

// ======================
// INPUT VALIDATION AND PARSING
// ======================

void				flood_fill(t_game *gunstorm, t_map *map, int x, int y);
void				validate_identifiers(char *map, t_game *gunstorm);
void				input_parsing(char *map_file, t_game *gunstorm);
void				validate_map_walls(t_game *gunstorm, t_map map);
void				validate_textures(char *map, t_game *gunstorm);
void				validate_colors(char *map, t_game *gunstorm);
void				validate_map(char *scene, t_game *gunstorm);
void				store_player(t_game *gunstorm);
bool				valid_map_char(char a);
bool				player_char(char a);

// ======================
// STRING UTILS
// ======================

void				check_color(t_game *gunstorm, char *map, char *id,
						bool *key_flag);
int					find(char *str, char *substr);
int					check_line(char *line, int s);
bool				empty_line(char *line, int s);
char				*get_color_line(char *map);
int					get_cell_color(char cell);
bool				valid_map_char(char a);
bool				player_char(char a);
bool				valid_char(char a);
bool				is_space(char c);

// ======================
// CORE FUNCTION
// ======================

void				game_core(char *map_file);

#endif // !GUNSTORM_BONUS_H
