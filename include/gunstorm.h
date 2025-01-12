#ifndef GUNSTORM_H

# define GUNSTORM_H

# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include "../libft/libft.h"

#define MAG "\e[0;35m"

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
	int	x;
	int	y;
}	t_pair;

typedef struct s_player
{
	t_pair 	position;
	char	direction;
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

typedef struct s_game
{
	t_texture	texture;
	t_rgb		floor;
	t_rgb		ceiling;
	t_map		map;
	t_player	player;
}	t_game;

bool	valid_map_char(char a);
bool	player_char(char a);
void	validate_map_walls(t_game *gunstorm, t_map map);
void	flood_fill(t_game *gunstorm, t_map *map, t_pair pos);
void	map_error(char *error_msg, t_game *gunstorm, char *map);
void	map_error_split(char *error_msg, t_game *gunstorm, char *map);

#endif // !GUNSTORM_H
