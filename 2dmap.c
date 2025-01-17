#include "include/gunstorm.h"

# define SPEED 4
# define CELL_SIZE 40
# define CELL_SIZE 40
# define FOV 60.0 
# define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0)

int	get_cell_color(char cell)
{
	if (cell == '0' || player_char(cell))
		return (0xFFFFFFFF);
	if (cell == '1')
		return (0x009e98cf);
	return (0x00000000);
}

void	draw_cube(mlx_image_t *img, int x, int y, char cell)
{
	int	i;
	int	j;

	i = 1;
	while (i < CELL_SIZE)
	{
		j = 1;
		while (j < CELL_SIZE)
		{
			mlx_put_pixel(img, x + i, y + j, get_cell_color(cell));
			j++;
		}
		i++;
	}
}

void	draw_player(mlx_image_t *img, t_pair position)
{
	int	i;
	int	j;

	i = 0;
	while (i < CELL_SIZE / 6)
	{
		j = 0;
		while (j < CELL_SIZE / 6)
		{
			mlx_put_pixel(img, position.x + i, position.y + j, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

size_t	map_width(t_map map)
{
	size_t	width;
	int		i;

	width = 0;
	i = 0;
	while (i < map.height)
	{
		if (ft_strlen(map.rows[i]) > width)
			width = ft_strlen(map.rows[i]);
		i++;
	}
	return (width);
}

bool	is_colliding(float x, float y, t_map map)
{
	int	map_x;
	int	map_y;

	map_x = floorf(x / CELL_SIZE);
	map_y = floorf(y / CELL_SIZE);
	if (map_x >= 0 && map_y >= 0
		&& map.rows[map_y][map_x] == '1')
		return (true);
	return (false);
}

void	check_boundries(t_pair *player, float new_x, float new_y, t_map map)
{
	if (is_colliding(new_x, new_y, map))
		return ;
	player->x = new_x;
	player->y = new_y;
}

void	hooks(mlx_key_data_t key, void *param)
{
	t_game	*gunstorm;

	gunstorm = (t_game *)param;
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_W))
		check_boundries(&gunstorm->player.position, gunstorm->player.position.x,
				  gunstorm->player.position.y - SPEED, gunstorm->map);
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_S))
		check_boundries(&gunstorm->player.position, gunstorm->player.position.x,
				  gunstorm->player.position.y + SPEED, gunstorm->map);
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_D))
		check_boundries(&gunstorm->player.position, gunstorm->player.position.x + SPEED,
				  gunstorm->player.position.y, gunstorm->map);
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_A))
		check_boundries(&gunstorm->player.position, gunstorm->player.position.x - SPEED,
				  gunstorm->player.position.y, gunstorm->map);
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_LEFT))
		gunstorm->player.angle -= 0.2;
	if (mlx_is_key_down(gunstorm->mlx_data.mlx, MLX_KEY_RIGHT))
		gunstorm->player.angle += 0.2;
}

void draw_line(mlx_image_t *img, float startX, float startY, float endX, float endY, uint32_t color)
{
    float deltaX = endX - startX;
    float deltaY = endY - startY;
    float step = fmax(fabs(deltaX), fabs(deltaY));

    deltaX /= step;
    deltaY /= step;

    float x = startX;
    float y = startY;

    for (int i = 0; i <= step; i++)
	{
        if (x >= 0 && x < img->width && y >= 0 && y < img->height)
            mlx_put_pixel(img, (int)x, (int)y, color);
        x += deltaX;
        y += deltaY;
    }
}

void cast_rays(int w, int h, t_map worldMap, t_mlx mlx_data, t_game *gunstorm)
{
	double playerX = gunstorm->player.position.x;
	double playerY = gunstorm->player.position.y;
	double posX = playerX / CELL_SIZE;
	double posY = playerY / CELL_SIZE;
	double playerDir = gunstorm->player.angle;

	double halfFOV = DEG_TO_RAD(FOV / 2.0);
	double startAngle = playerDir - halfFOV;

	for (int x = 0; x < w; x++)
	{
		double rayAngle = startAngle + (2 * halfFOV * x / (double)w);
		double rayDirX = cos(rayAngle);
		double rayDirY = sin(rayAngle);

		int mapX = (int)posX;
		int mapY = (int)posY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

		double sideDistX, sideDistY;
		int stepX, stepY;
		int hit = 0;
		int side = 0;  // 0 for vertical, 1 for horizontal

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
	{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}

		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
	{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		double wallX = posX;
		double wallY = posY;

		// DDA algorithm
		while (!hit)
		{
			if (sideDistX < sideDistY) {
				wallX = mapX + (stepX > 0 ? 1.0 : 0.0);
				wallY = posY + (wallX - posX) * rayDirY / rayDirX;
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				wallY = mapY + (stepY > 0 ? 1.0 : 0.0);
				wallX = posX + (wallY - posY) * rayDirX / rayDirY;
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (mapX >= 0 && mapX < map_width(worldMap) && 
				mapY >= 0 && mapY < worldMap.height && 
				worldMap.rows[mapY][mapX] == '1') {
				hit = 1;
			}
		}

		double endX = wallX * CELL_SIZE;
		double endY = wallY * CELL_SIZE;

		draw_line(mlx_data.img, playerX, playerY, endX, endY, 0x000000FF);
	}
}

void	map(void *param)
{
	t_game	*gunstorm;
	int		i;
	int		j;

	gunstorm = (t_game *)param;
	i = 0;
	gunstorm->frames++;
	if (mlx_get_time() - gunstorm->start_time >= 1)
	{
		printf("FPS: %d\n", gunstorm->frames);
		gunstorm->frames = 0;
		gunstorm->start_time = mlx_get_time();
	}
	while (i < gunstorm->map.height)
	{
		j = 0;
		while (j < (int)ft_strlen(gunstorm->map.rows[i]))
		{
			draw_cube(gunstorm->mlx_data.img, j * CELL_SIZE,
				i * CELL_SIZE, gunstorm->map.rows[i][j]);
			j++;
		}
		i++;
	}
	draw_player(gunstorm->mlx_data.img, gunstorm->player.position);
	cast_rays(map_width(gunstorm->map) * 40, gunstorm->map.height * 40,
			gunstorm->map, gunstorm->mlx_data, gunstorm);
}

void	map_2d(t_game *gunstorm)
{
	int		width;
	int		height;
	mlx_t	*mlx;
	mlx_image_t	*img;

	width = CELL_SIZE * map_width(gunstorm->map);
	height = CELL_SIZE * gunstorm->map.height;
	gunstorm->player.position.x *= CELL_SIZE;
	gunstorm->player.position.y *= CELL_SIZE;
	gunstorm->player.position.x += (float)CELL_SIZE / 2;
	gunstorm->player.position.y += (float)CELL_SIZE / 2;
	mlx = mlx_init(width, height, "2D Map", true);
	if (!mlx)
		exit(4);
	img = mlx_new_image(mlx, width, height);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		exit(4);
	gunstorm->mlx_data.mlx = mlx;
	gunstorm->mlx_data.img = img;
	gunstorm->start_time = mlx_get_time();
	gunstorm->frames = 0;
	mlx_loop_hook(mlx, map, gunstorm);
	mlx_key_hook(mlx, hooks, gunstorm);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
