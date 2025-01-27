#include "../../include/gunstorm.h"

static void	draw_player_icon(mlx_image_t *img, t_pair pos)
{
	int	px;
	int	py;

	px = 0;
	while (px < CELL_SIZE / 2)
	{
		py = 0;
		while (py < CELL_SIZE / 2)
		{
			mlx_put_pixel(img, pos.x + px, pos.y + py, 0x35deedcc);
			py++;
		}
		px++;
	}
}

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
		mx = 100
			+ (px - gunstorm->player.position.x) * 3;
		my = 100
			+ (py - gunstorm->player.position.y) * 3;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				mlx_put_pixel(gunstorm->mlx_data.img, mx + j, my + i, col);
			}
		}
	}
}
static void	draw_minimap_cell(t_game *gunstorm, int cx, int cy, char type)
{
	int		px;
	int		py;
	int		col;

	col = get_cell_color(type);
	px = 0;
	draw_player_icon(gunstorm->mlx_data.img, (t_pair){100, 100});
	while (px < CELL_SIZE)
	{
		py = 0;
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
