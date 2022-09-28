/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roue_libre2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:26:50 by rbony             #+#    #+#             */
/*   Updated: 2022/08/15 18:21:18 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

float	degtorad(int a)
{
	return (a * M_PI / 180.0);
}

int	fixang(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
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

void	draw_line(t_game *game, int x, int y, int len)
{
	float			i;
	int				width;
	int				tmpx;
	int				tmpy;

	width = 0;
	while (width < 8)
	{
		i = 0.0;
		while (i <= 1.0)
		{
			tmpx = x + (x - x) * i;
			tmpy = y + (len - y) * i;
			my_mlx_pixel_put(game, tmpx, tmpy, 0xFF0000);
			i += 0.0001;
		}
		x++;
		width++;
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
				my_mlx_pixel_put(game, j, i, 0xDDDDDD);
			else
				my_mlx_pixel_put(game, j, i, 0x333333);
			j++;
		}
		i++;
	}
}

void	check_vertical(t_game *game, t_player p, int **map, t_raycasting *ra)
{
	float	tan;

	ra->dof = 0;
	tan = tanf(degtorad(ra->ra));
	if (cos(degtorad(ra->ra)) > 0.001)
	{
		ra->rx = (((int)p.px >> 6) << 6) + 64;
		ra->ry = (p.px - ra->rx) * tan + p.py;
		ra->xo = 64;
		ra->yo = -ra->xo * tan;
	}
	else if (cos(degtorad(ra->ra)) < -0.001)
	{
		ra->rx = (((int)p.px >> 6) << 6) - 0.0001;
		ra->ry = (p.px - ra->rx) * tan + p.py;
		ra->xo = -64;
		ra->yo = -ra->xo * tan;
	}
	else
	{
		ra->rx = p.px;
		ra->ry = p.py;
		ra->dof = 8;
	}
	while (ra->dof < 8)
	{
		ra->mx = (int)(ra->rx) >> 6;
		ra->my = (int)(ra->ry) >> 6;
		if (ra->mp > 0 && ra->mp < game->map_width * game->map_height && map[ra->mx][ra->my] == 1)
		{
			ra->dof = 8;
			ra->disv = cos(degtorad(ra->ra)) * (ra->rx - p.px) - sin(degtorad(ra->ra)) * (ra->ry - p.py);
		}
		else
		{
			ra->rx += ra->xo;
			ra->ry += ra->yo;
			ra->dof += 1;
		}
	}
	ra->vx = ra->rx;
	ra->vy = ra->ry;
}

void	check_horizontal(t_game *game, t_player p, int **map, t_raycasting *ra)
{
	float	tan;

	ra->dof = 0;
	tan = 1.0 / tanf(degtorad(ra->ra));
	if (sin(degtorad(ra->ra)) > 0.001)
	{
		ra->ry = (((int)p.py >> 6) << 6) - 0.0001;
		ra->rx = (p.py - ra->ry) * tan + p.px;
		ra->yo = -64;
		ra->xo = -ra->yo * tan;
	}
	else if (sin(degtorad(ra->ra)) < -0.001)
	{
		ra->ry = (((int)p.py >> 6) << 6) + 64;
		ra->rx = (p.py - ra->ry) * tan + p.px;
		ra->yo = 64;
		ra->xo = -ra->yo * tan;
	}
	else
	{
		ra->rx = p.px;
		ra->ry = p.py;
		ra->dof = 8;
	}
	while (ra->dof < 8)
	{
		ra->mx = (int)(ra->rx) >> 6;
		ra->my = (int)(ra->ry) >> 6;
		if (ra->mp > 0 && ra->mp < game->map_width * game->map_height && map[ra->mx][ra->my] == 1)
		{
			ra->dof = 8;
			ra->dish = cos(degtorad(ra->ra)) * (ra->rx - p.px) - sin(degtorad(ra->ra)) * (ra->ry - p.py);
		}
		else
		{
			ra->rx += ra->xo;
			ra->ry += ra->yo;
			ra->dof += 1;
		}
	}
}

void	draw(t_game *game)
{
	int				r;
	t_raycasting	ray;

	draw_background(game);
	ray.ra = fixang(game->player.pa + 30);
	ray.disv = 100000;
	ray.dish = 100000;
	r = 0;
	while (r < 60)
	{
		check_vertical(game, game->player, game->map, &ray);
		check_horizontal(game, game->player, game->map, &ray);
		if (ray.disv < ray.dish)
		{
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			ray.dish = ray.disv;
		}
		ray.ca = fixang(game->player.pa - ray.ra);
		ray.dish = ray.dish * cos(degtorad(ray.ca));
		ray.lineh = (64 * 320) / (ray.dish);
		if (ray.lineh > 320)
			ray.lineh = 320;
		draw_line(game, r * 8, game->win_width - ray.lineh, ray.lineh);
		ray.ra = fixang(ray.ra - 1);
		r++;
	}
}
