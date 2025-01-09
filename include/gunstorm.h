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
}	t_game;

#endif // !GUNSTORM_H
