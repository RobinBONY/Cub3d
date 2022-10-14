/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:32:48 by rbony             #+#    #+#             */
/*   Updated: 2022/10/12 15:16:02 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > game->win_width - 1 || y < 0 || y > game->win_height - 1)
		return ;
	dst = game->img.addr + (y * game->img.line_length + x
			* (game->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	set_color(int side)
{
	if (side == 1)
		return (0xFF0000);
	else if (side == 2)
		return (0x00FF00);
	else if (side == 3)
		return (0x0000FF);
	else
		return (0xFFFF00);
}

void	draw_column(t_game *game, int x, t_raycasting *ray)
{
	int	i;
	int	y;
	int	len;
	int	tmpy;

	len = (int)(64 * game->win_height / ray->dist.x);
	if (len > game->win_height)
		len = game->win_height;
	y = game->win_height / 2 - len / 2;
	i = 0;
	while (y + i < y + len)
	{
		tmpy = y + i;
		my_mlx_pixel_put(game, x, tmpy, set_color(ray->hcolor));
		i++;
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

void	raycasting(t_game *game)
{
	int				nbr;
	t_raycasting	ray;
	t_point			col;

	draw_background(game);
	draw_map(game);
	nbr = 0;
	ray.ra = fixang(game->player.pa + ((M_PI / 180) * 35));
	while (nbr < game->win_width)
	{
		dda(game, &ray);
		if (ray.dist.y < ray.dist.x)
		{
			ray.ray.x = ray.vertical.x;
			ray.ray.y = ray.vertical.y;
			ray.dist.x = ray.dist.y;
			ray.hcolor = ray.vcolor;
		}
		col = create_vect(game->player.pos, ray.ra, ray.dist.x);
		ray.dist.x = ray.dist.x * cos(fixang(ray.ra - game->player.pa));
		brest(game, game->player.pos.x, game->player.pos.y, col.x, col.y, set_color(ray.hcolor));
		draw_column(game, nbr, &ray);
		nbr++;
		ray.ra = fixang(ray.ra - ((M_PI / 180) * 70) / game->win_width );
	}
}
// distV = ray.dist.y
// distH = ray.dist.x