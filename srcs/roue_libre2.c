/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roue_libre2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:26:50 by rbony             #+#    #+#             */
/*   Updated: 2022/08/17 17:47:33 by rbony            ###   ########lyon.fr   */
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
	int				tmpx;
	int				tmpy;

	i = 0.0;
	while (i <= 1.0)
	{
		tmpx = x + (x - x) * i;
		tmpy = y + ((y + len) - y) * i;
		my_mlx_pixel_put(game, tmpx, tmpy, 0xFF0000);
		i += 0.001;
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

void	nearest_point(t_raycasting *ray)
{
	int	dx;
	int	dy;

	dx = pow(ray->cx.x - ray->c.x, 2) + pow(ray->cx.y - ray->c.y, 2);
	dy = pow(ray->cy.x - ray->c.x, 2) + pow(ray->cy.y - ray->c.y, 2);
	if (dx < dy)
		ray->c = ray->cx;
	else
		ray->c = ray->cy;
}

int	in_map(t_game *game, int x, int y)
{
	if (x > 0 && y > 0 && x < game->map_width && y < game->map_height)
		return (1);
	return (0);
}

double	top_right(t_game *game, t_raycasting *ray)
{
	ray->c = game->player;
	while (in_map(game, ray->c.x / 64, (ray->c.y - 1) / 64)
		&& game->map[(ray->c.y - 1) / 64][ray->c.x / 64] != 1)
	{
		ray->cx = ray->c;
		ray->cy = ray->c;
		ray->dx = 64 - (ray->c.x % 64);
		ray->dy = ray->c.y % 64;
		if (ray->dx == 0)
			ray->dx = 64;
		if (ray->dy == 0)
			ray->dy = 64;
		if (ray->ra == 0)
			ray->c.x += ray->dx;
		else
		{
			ray->cx.x += ray->dx;
			ray->cx.y -= tan(ray->ra) * ray->dx;
			ray->cy.x += tan(M_PI / 2 - ray->ra) * ray->dy;
			ray->cy.y -= ray->dy;
		}
		nearest_point(ray);
	}
	return (sqrt(pow(game->player.x - ray->c.x, 2)
			+ pow(game->player.y - ray->c.y, 2)));
}

double	top_left(t_game *game, t_raycasting *ray)
{
	ray->c = game->player;
	while (in_map(game, (ray->c.x - 1) / 64, (ray->c.y - 1) / 64)
		&& game->map[(ray->c.y - 1) / 64][(ray->c.x - 1) / 64] != 1)
	{
		ray->cx = ray->c;
		ray->cy = ray->c;
		ray->dx = ray->c.x % 64;
		ray->dy = ray->c.y % 64;
		if (ray->dx == 0)
			ray->dx = 64;
		if (ray->dy == 0)
			ray->dy = 64;
		if (ray->ra == M_PI / 2)
			ray->c.y -= ray->dy;
		else
		{
			ray->cx.x -= ray->dx;
			ray->cx.y -= tan(M_PI / 2 - (ray->ra - (M_PI / 2))) * ray->dx;
			ray->cy.x -= tan(ray->ra - (M_PI / 2)) * ray->dy;
			ray->cy.y -= ray->dy;
		}
		nearest_point(ray);
	}
	return (sqrt(pow(game->player.x - ray->c.x, 2)
			+ pow(game->player.y - ray->c.y, 2)));
}

double	bot_left(t_game *game, t_raycasting *ray)
{
	ray->c = game->player;
	while (in_map(game, (ray->c.x - 1) / 64, ray->c.y / 64)
		&& game->map[ray->c.y / 64][(ray->c.x - 1) / 64] != 1)
	{
		ray->cx = ray->c;
		ray->cy = ray->c;
		ray->dx = ray->c.x % 64;
		ray->dy = 64 - (ray->c.y % 64);
		if (ray->dx == 0)
			ray->dx = 64;
		if (ray->dy == 0)
			ray->dy = 64;
		if (ray->ra == M_PI)
			ray->c.x -= ray->dx;
		else
		{
			ray->cx.x -= ray->dx;
			ray->cx.y += tan(ray->ra - M_PI) * ray->dx;
			ray->cy.x -= tan(M_PI / 2 - (ray->ra - M_PI)) * ray->dy;
			ray->cy.y += ray->dy;
		}
		nearest_point(ray);
	}
	return (sqrt(pow(game->player.x - ray->c.x, 2)
			+ pow(game->player.y - ray->c.y, 2)));
}

double	bot_right(t_game *game, t_raycasting *ray)
{
	ray->c = game->player;
	while (in_map(game, ray->c.x / 64, ray->c.y / 64)
		&& game->map[ray->c.y / 64][ray->c.x / 64] != 1)
	{
		ray->cx = ray->c;
		ray->cy = ray->c;
		ray->dx = 64 - (ray->c.x % 64);
		ray->dy = 64 - (ray->c.y % 64);
		if (ray->dx == 0)
			ray->dx = 64;
		if (ray->dy == 0)
			ray->dy = 64;
		if (ray->ra == (3 * (M_PI / 2)))
			ray->c.y += ray->dy;
		else
		{
			ray->cx.x += ray->dx;
			ray->cx.y += tan(M_PI / 2 - (ray->ra - (3 * (M_PI / 2)))) * ray->dx;
			ray->cy.x += tan(ray->ra - (3 * (M_PI / 2))) * ray->dy;
			ray->cy.y += ray->dy;
		}
		nearest_point(ray);
	}
	return (sqrt(pow(game->player.x - ray->c.x, 2)
			+ pow(game->player.y - ray->c.y, 2)));
}

void	raycasting(t_game *game)
{
	int				r;
	double			dist;
	t_raycasting	ray;

	draw_background(game);
	ray.ra = game->pa + (M_PI / 3) / 2;
	r = 0;
	while (r < game->win_width)
	{
		if (ray.ra >= 0 && ray.ra < (M_PI / 2))
			dist = top_right(game, &ray);
		if (ray.ra >= (M_PI / 2) && ray.ra < M_PI)
			dist = top_left(game, &ray);
		if (ray.ra >= M_PI && ray.ra < (3 * (M_PI / 2)))
			dist = bot_left(game, &ray);
		if (ray.ra >= (3 * (M_PI / 2)) && ray.ra < (2 * M_PI))
			dist = bot_right(game, &ray);
		//brest(game, game->player.x, game->player.y, ray.c.x, ray.c.y);
		draw_line(game, r, game->win_height / 2, dist);
		r++;
		ray.ra = fixang(ray.ra + (M_PI / 3) / (game->win_width));
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
