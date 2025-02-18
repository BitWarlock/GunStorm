/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:06:26 by mrezki            #+#    #+#             */
/*   Updated: 2025/02/16 19:24:32 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/gunstorm.h"

static void	rotate_point(float *x, float *y, float angle)
{
	float	rad;
	float	cos_theta;
	float	sin_theta;
	float	x_new;
	float	y_new;

	rad = angle * (M_PI / 180.0);
	cos_theta = cos(rad);
	sin_theta = sin(rad);
	x_new = *x * cos_theta - *y * sin_theta;
	y_new = *x * sin_theta + *y * cos_theta;
	*x = x_new;
	*y = y_new;
}

// Function to rotate and translate points
void	rotate_and_translate_points(t_pair points[3],
			t_pair pos, float angle)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		rotate_point(&points[i].x, &points[i].y, angle);
		points[i].x += pos.x;
		points[i].y += pos.y;
		i++;
	}
}

// Function to sort points by y-coordinate
void	sort_points_by_y(t_pair points[3])
{
	t_pair	temp;
	int		i;
	int		j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2 - i)
		{
			if (points[j].y > points[j + 1].y)
			{
				temp = points[j];
				points[j] = points[j + 1];
				points[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	fill_helper(t_pair pts[3], float *left_x, float *right_x, float py)
{
	if (py < pts[1].y)
	{
		*left_x = pts[0].x + (pts[1].x - pts[0].x)
			* (py - pts[0].y) / (pts[1].y - pts[0].y);
		*right_x = pts[0].x + (pts[2].x - pts[0].x)
			* (py - pts[0].y) / (pts[2].y - pts[0].y);
	}
	else
	{
		*left_x = pts[1].x + (pts[2].x - pts[1].x)
			* (py - pts[1].y) / (pts[2].y - pts[1].y);
		*right_x = pts[0].x + (pts[2].x - pts[0].x)
			* (py - pts[0].y) / (pts[2].y - pts[0].y);
	}
}

// Function to fill the triangle
void	fill_triangle(mlx_image_t *img, t_pair pts[3], uint32_t color)
{
	float	py;
	float	left_x;
	float	right_x;
	float	temp;
	int		f;

	py = pts[0].y;
	while (py <= pts[2].y)
	{
		if (py >= 0 && py < img->height)
		{
			fill_helper(pts, &left_x, &right_x, py);
			if (left_x > right_x)
				(1 && (temp = left_x), (left_x = right_x), (right_x = temp));
			left_x = fmax(0, fmin(left_x, img->width - 1));
			right_x = fmax(0, fmin(right_x, img->width - 1));
			f = (int)left_x;
			while (f <= (int)right_x)
				mlx_put_pixel(img, f++, (int)py, color);
		}
		py++;
	}
}
