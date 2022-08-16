/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roue_libre2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:26:50 by rbony             #+#    #+#             */
/*   Updated: 2022/08/16 18:10:20 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	fixang(int a)
{
	if (a > (2 * M_PI))
		a -= (2 * M_PI);
	if (a < 0)
		a += (2 * M_PI);
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
	while (width < 63)
	{
		i = 0.0;
		while (i <= 1.0)
		{
			tmpx = x + (x - x) * i;
			tmpy = y + ((y + len) - y) * i;
			my_mlx_pixel_put(game, tmpx, tmpy, 0xFF0000);
			i += 0.001;
		}
		x++;
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
				my_mlx_pixel_put(game, j, i, 0xDDDDDD);
			else
				my_mlx_pixel_put(game, j, i, 0x333333);
			j++;
		}
		i++;
	}
}

int	in_map(t_game *game, int x, int y)
{
	if (x < game->map_width && y < game->map_height)
		return (1);
	return (0);
}

void	top_right(t_game *game, t_player p, t_raycasting *ray)
{
	ray->dof = 0;
	ray->cx = p.px;
	ray->cy = p.py;
	while (in_map(game, ray->cx / 64, ray->cy / 64)
		&& game->map[ray->cy / 64][ray->cx / 64] != 1)
	{
		ray->cx++;
		ray->cy--;
		ray->dx = 64 - (ray->cx % 64);
		ray->dy = ray->cy % 64;
		if (ray->ra == 0)
			ray->cx += ray->dx;
		else if (ray->dx < ray->dy)
		{
			ray->cx += ray->dx;
			ray->cy -= ray->atan * ray->dx;
		}
		else
		{
			ray->cx += ray->atan * ray->dy;
			ray->cy -= ray->dy;
		}
	}
}

void	top_left(t_game *game, t_player p, t_raycasting *ray)
{
	ray->dof = 0;
	ray->cx = p.px;
	ray->cy = p.py;
	while (in_map(game, ray->cx / 64, ray->cy / 64)
		&& game->map[ray->cy / 64][ray->cx / 64] != 1)
	{
		ray->cx--;
		ray->cy--;
		ray->dx = ray->cx % 64;
		ray->dy = ray->cy % 64;
		if (ray->ra == M_PI / 2)
			ray->cy -= ray->dy;
		else if (ray->dx < ray->dy)
		{
			ray->cx -= ray->dx;
			ray->cy -= ray->atan * ray->dx;
		}
		else
		{
			ray->cx -= ray->atan * ray->dy;
			ray->cy -= ray->dy;
		}
	}
}

void	bot_left(t_game *game, t_player p, t_raycasting *ray)
{
	ray->dof = 0;
	ray->cx = p.px;
	ray->cy = p.py;
	while (in_map(game, ray->cx / 64, ray->cy / 64)
		&& game->map[ray->cy / 64][ray->cx / 64] != 1)
	{
		ray->cx--;
		ray->cy++;
		ray->dx = ray->cx % 64;
		ray->dy = 64 - (ray->cy % 64);
		if (ray->ra == M_PI)
			ray->cx -= ray->dx;
		else if (ray->dx < ray->dy)
		{
			ray->cx -= ray->dx;
			ray->cy += ray->atan * ray->dx;
		}
		else
		{
			ray->cx -= ray->atan * ray->dy;
			ray->cy += ray->dy;
		}
	}
}

void	bot_right(t_game *game, t_player p, t_raycasting *ray)
{
	ray->dof = 0;
	ray->cx = p.px;
	ray->cy = p.py;
	while (in_map(game, ray->cx / 64, ray->cy / 64)
		&& game->map[ray->cy / 64][ray->cx / 64] != 1)
	{
		ray->cx++;
		ray->cy++;
		ray->dx = 64 - (ray->cx % 64);
		ray->dy = 64 - (ray->cy % 64);
		if (ray->ra == (3 * (M_PI / 2)))
			ray->cy += ray->dy;
		else if (ray->dx < ray->dy)
		{
			ray->cx += ray->dx;
			ray->cy += ray->atan * ray->dx;
		}
		else
		{
			ray->cx += ray->atan * ray->dy;
			ray->cy += ray->dy;
		}
	}
}

void	raycasting(t_game *game)
{
	int				r;
	t_raycasting	ray;

	ray.ra = game->player.pa;
	r = 0;
	while (r < 1)
	{
		printf("%f\n", ray.ra);
		ray.atan = tanf(ray.ra);
		if (ray.ra >= 0 && ray.ra < (M_PI / 2))
			top_right(game, game->player, &ray);
		if (ray.ra >= (M_PI / 2) && ray.ra < M_PI)
			top_left(game, game->player, &ray);
		if (ray.ra >= M_PI && ray.ra < (3 * (M_PI / 2)))
			bot_left(game, game->player, &ray);
		if (ray.ra >= (3 * (M_PI / 2)) && ray.ra < (2 * M_PI))
			bot_right(game, game->player, &ray);
		printf("%d %d\n", ray.cx, ray.cy);
		brest(game, game->player.px, game->player.py, ray.cx, ray.cy);
		r++;
		ray.ra = fixang(game->player.pa - r);
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;
	int	centerx;
	int	centery;

	draw_background(game);
	centerx = game->map_width / 2;
	centery = game->map_height / 2;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 1)
				draw_line(game, j * 64, i * 64, 63);
			j++;
		}
		i++;
	}
}
