/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roue_libre2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:26:50 by rbony             #+#    #+#             */
/*   Updated: 2022/09/07 12:34:51 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

double	fixang(double a)
{
	if (a >= ((double)2 * M_PI))
		a -= ((double)2 * M_PI);
	if (a < 0)
		a += ((double)2 * M_PI);
	return (a);
}

int	check_tan(double t)
{
	if (t > -0.005 && t < 0.005)
		return (1);
	return (0);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > game->win_width - 1 || y < 0 || y > game->win_height - 1)
		return ;
	dst = game->img.addr + (y * game->img.line_length + x
			* (game->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_column(t_game *game, int x, int y, int len)
{
	int	i;
	int	tmpy;

	i = 0;
	while (y + i < y + len)
	{
		tmpy = y + i;
		my_mlx_pixel_put(game, x, tmpy, 0xFF0000);
		i++;
	}
}

void	draw_square(t_game *game, int x, int y, int len)
{
	int				width;

	width = 0;
	while (width < len)
	{
		draw_column(game, x + width, y, len);
		width++;
	}
}

void	brest(t_game *env, int sx, int sy, int ex, int ey)
{
	float	i;
	int		tmpx;
	int		tmpy;

	i = 0.0;
	while (i <= 1.0)
	{
		tmpx = sx + (ex - sx) * i;
		tmpy = sy + (ey - sy) * i;
		my_mlx_pixel_put(env, tmpx, tmpy, 0x00FF00);
		i += 0.0001;
	}
}

void	draw_background(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->win_height)
	{
		j = 0;
		while (j < game->win_width)
		{
			if (i < game->win_height / 2)
				my_mlx_pixel_put(game, j, i, 0xC0DFEF);
			else
				my_mlx_pixel_put(game, j, i, 0x333333);
			j++;
		}
		i++;
	}
}

int	in_map(t_game *game, int x, int y)
{
	if (x > 0 && y > 0 && x < game->map_width && y < game->map_height)
		return (1);
	return (0);
}

t_point	create_vect(t_point origin, double radian, double length)
{
	t_point	vector;

	vector.x = cos(-radian) * length + origin.x;
	vector.y = sin(-radian) * length + origin.y;
	return (vector);
}

t_vector	init_vector(t_point start, t_point dest)
{
	t_vector	v;

	v.dx = dest.x - start.x;
	v.dy = dest.y - start.y;
	return (v);
}

t_raycasting	dda(t_game *game, float ra)
{
	t_raycasting		ray;

	ray.map_x = (int)game->player.x;
	ray.map_y = (int)game->player.y;
	ray.dir = init_vector(game->player, create_vect(game->player, ra, 3));
	if (ray.dir.dx == 0.0f)
		ray.delta_dist.dx = 1e30;
	else
		ray.delta_dist.dx = fabsf(1.0f / ray.dir.dx);
	if (ray.dir.dy == 0.0f)
		ray.delta_dist.dy = 1e30;
	else
		ray.delta_dist.dy = fabsf(1.0f / ray.dir.dy);
	//
	if (ray.dir.dx < 0)
	{
		ray.step.x = -1;
		ray.side_dist.dx = (game->player.x - ray.map_x) * ray.delta_dist.dx;
	}
	else
	{
		ray.step.x = 1;
		ray.side_dist.dx = (ray.map_x + 1.0f - game->player.x)
			* ray.delta_dist.dx;
	}
	if (ray.dir.dy < 0)
	{
		ray.step.y = -1;
		ray.side_dist.dy = (game->player.y - ray.map_y) * ray.delta_dist.dy;
	}
	else
	{
		ray.step.y = 1;
		ray.side_dist.dy = (ray.map_y + 1.0f - game->player.y)
			* ray.delta_dist.dy;
	}
	//
	while (1)
	{
		if (ray.side_dist.dx < ray.side_dist.dy)
		{
			ray.side_dist.dx += ray.delta_dist.dx;
			ray.map_x += ray.step.x;
			ray.side_hit.x = ray.step.x;
			ray.side_hit.y = 0;
		}
		else
		{
			ray.side_dist.dy += ray.delta_dist.dy;
			ray.map_y += ray.step.y;
			ray.side_hit.y = ray.step.y;
			ray.side_hit.x = 0;
		}
		if (game->map[ray.map_y][ray.map_x] == 1)
		{
			if (ray.side_hit.y == 0)
				ray.perp_dist = (ray.side_dist.dx - ray.delta_dist.dx)
					* game->cellsize;
			else
				ray.perp_dist = (ray.side_dist.dy - ray.delta_dist.dy)
					* game->cellsize;
			if (ray.side_hit.x == 1)
				ray.side = 3;
			else if (ray.side_hit.x == -1)
				ray.side = 1;
			else if (ray.side_hit.y == 1)
				ray.side = 0;
			else
				ray.side = 2;
			return (ray);
		}
	}
	return (ray);
}

void	raycasting(t_game *game)
{
	int		nbr;
	float	ra;
	t_raycasting	ray;

	//draw_background(game);
	nbr = 0;
	ra = game->pa - (M_PI / 3) / 2;
	while (nbr < game->win_width)
	{
		ray = dda(game, ra);
		brest(game, game->player.x * 64, game->player.y * 64, ray.side_dist.dx * 64, ray.side_dist.dy * 64);
		ra += (M_PI / 3) / game->win_width;
		nbr++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	draw_background(game);
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 1)
				draw_square(game, j * 64, i * 64, 63);
			j++;
		}
		i++;
	}
}
