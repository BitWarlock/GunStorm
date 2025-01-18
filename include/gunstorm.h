/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gunstorm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:10:29 by mrezki            #+#    #+#             */
/*   Updated: 2025/01/18 18:20:31 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUNSTORM_H

# define GUNSTORM_H

# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 720
# define FOV M_PI / 3
# define HALF_FOV FOV / 2
# define CELL_SIZE 32
# define SPEED CELL_SIZE / 8
# define MAG "\e[0;35m"
# define RED "\e[0;31m"
# define RESET "\e[0m"

typedef struct s_identifiers
{
	bool	no;
	bool	so;
	bool	ea;
	bool	we;
	bool	f;
	bool	c;
}	t_identifiers;

typedef struct s_pair
{
	float	x;
	float	y;
}	t_pair;

typedef struct s_player
{
	t_pair	position;
	char	direction;
	float	angle;
}	t_player;

typedef struct s_map
{
	char	**rows;
	int		height;
}	t_map;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}		t_texture;

typedef struct s_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_mlx;

typedef struct s_raycaster
{
	int		side;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	float	wall_x;
	float	wall_y;
	float	player_x;
	float	player_y;
	float	ray_dirx;
	float	ray_diry;
	float	ray_angle;
	float	delta_distx;
	float	delta_disty;
	float	side_distx;
	float	side_disty;
}	t_raycaster;

typedef struct s_game
{
	t_texture	texture;
	t_player	player;
	t_rgb		floor;
	t_rgb		ceiling;
	t_map		map;
	t_mlx		mlx_data;
	t_raycaster	ray;
	double		start_time;
	int			frames;
}	t_game;

void	game_fps(t_game *gunstorm);
void	game_hooks(mlx_key_data_t key, void *param);
void	raycaster(int width, t_game *gunstorm, bool map_2d);
size_t	map_width(t_map map);
void	map_2d(t_game *gunstorm);
void	print_gunstorm(t_game *gunstorm);

void	game_core(char *map_file);

/* ERROR HANDLING */

void	texture_error(char *error);
void	fatal_error(char *error, char *msg);
void	map_error(char *error_msg, t_game *gunstorm, char *map);
void	puterror(char *prefix, char *err1, char *err2, char *suffix);
void	map_error_split(char *error_msg, t_game *gunstorm, char *map);

/* MEMORY MANAGEMENT */

void	free_split(char **strs);
void	free_all(t_game *gunstorm);
void	free_game(t_game *gunstorm);
void	free_textures(char *map, t_game *gunstorm, int index);

/* INPUT VALIDATION AND PARSE */

bool	valid_map_char(char a);
bool	player_char(char a);

void	store_player(t_game *gunstorm);
void	validate_map(char *scene, t_game *gunstorm);
void	validate_colors(char *map, t_game *gunstorm);
void	validate_textures(char *map, t_game *gunstorm);
void	validate_map_walls(t_game *gunstorm, t_map map);
void	input_parsing(char *map_file, t_game *gunstorm);
void	validate_identifiers(char *map, t_game *gunstorm);
void	flood_fill(t_game *gunstorm, t_map *map, int x, int y);

/* STRING UTILS */

void	check_color(t_game *gunstorm,
			char *map, char *id, bool *key_flag);

bool	is_space(char c);
bool	valid_char(char a);
bool	player_char(char a);
bool	valid_map_char(char a);
bool	empty_line(char *line, int s);

char	*get_color_line(char *map);

int		find(char *str, char *substr);
int		check_line(char *line, int s);

#endif // !GUNSTORM_H
