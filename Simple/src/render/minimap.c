#include "../../include/gunstorm.h"

static bool	is_within_circle(t_pair c, int px, int py)
{
	float	dist;

	dist = ((px - c.x) * (px - c.x)) + ((py - c.y) * (py - c.y));
	return (dist <= (CELL_SIZE * 3) * (CELL_SIZE * 3));
}

static void	put_pixel_in_circle(t_game *gunstorm, int px, int py, int col)
{
	float	mx;
	float	my;

	if (is_within_circle(gunstorm->player.position, px, py))
	{
		mx = ((map_width(gunstorm->map) * CELL_SIZE) / 2.0)
			+ (px - gunstorm->player.position.x);
		my = ((gunstorm->map.height * CELL_SIZE) / 2.0)
			+ (py - gunstorm->player.position.y);
		mlx_put_pixel(gunstorm->mlx_data.img, mx, my, col);
	}
}

static void	draw_player_icon(mlx_image_t *img, t_pair pos)
{
	int	px;
	int	py;

	px = 0;
	while (px < CELL_SIZE / 6)
	{
		py = 0;
		while (py < CELL_SIZE / 6)
		{
			mlx_put_pixel(img, pos.x + px, pos.y + py, 0xFF0000FF);
			py++;
		}
		px++;
	}
}

static void	draw_minimap_cell(t_game *gunstorm, int cx, int cy, char type)
{
	int		px;
	int		py;
	int		col;

	col = get_cell_color(type);
	px = 1;
	draw_player_icon(gunstorm->mlx_data.img, (t_pair){
		(map_width(gunstorm->map) * CELL_SIZE) / 2.0,
		(gunstorm->map.height * CELL_SIZE) / 2.0});
	while (px < CELL_SIZE)
	{
		py = 1;
		while (py < CELL_SIZE)
		{
			put_pixel_in_circle(gunstorm, cx + px, cy + py, col);
			py++;
		}
		px++;
	}
}

void	minimap(t_game *gunstorm)
{
	int	cx;
	int	cy;
	int	cx_limit;
	int	cy_limit;

	cx = (gunstorm->player.position.x / CELL_SIZE) - 4;
	if (cx < 0)
		cx = 0;
	cx_limit = cx + 8;
	if (cx_limit >= map_width(gunstorm->map))
		cx_limit = map_width(gunstorm->map) - 1;
	while (cx <= cx_limit)
	{
		cy = (gunstorm->player.position.y / CELL_SIZE) - 4;
		if (cy < 0)
			cy = 0;
		cy_limit = cy + 8;
		if (cy_limit >= gunstorm->map.height)
			cy_limit = gunstorm->map.height - 1;
		while (cy <= cy_limit)
		{
			draw_minimap_cell(gunstorm, cx * CELL_SIZE, cy * CELL_SIZE,
				gunstorm->map.rows[cy][cx]);
			cy++;
		}
		cx++;
	}
}
