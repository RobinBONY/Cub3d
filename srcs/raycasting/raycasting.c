/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:32:48 by rbony             #+#    #+#             */
/*   Updated: 2022/10/18 15:22:35 by rbony            ###   ########lyon.fr   */
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

t_texture	set_texture(t_game *game, t_raycasting *ray)
{
	if (ray->hcolor == 1)
		return (game->map_info.w_texture);
	else if (ray->hcolor == 2)
		return (game->map_info.n_texture);
	else if (ray->hcolor == 3)
		return (game->map_info.e_texture);
	else
		return (game->map_info.s_texture);
}

void	draw_column(t_game *game, int x, t_raycasting *ray)
{
	int	i;
	int	y;
	int	len;

	len = (int)(128 * game->win_height / ray->dist.x);
	ray->rtexture = set_texture(game, ray);
	if (ray->hcolor % 2 == 0)
		ray->tx = ((ray->col.x / 64.0f) - (int)(ray->col.x / 64.0f))
			* ray->rtexture.width;
	else
		ray->tx = ((ray->col.y / 64.0f) - (int)(ray->col.y / 64.0f))
			* ray->rtexture.width;
	ray->ratio = (double)ray->rtexture.height / (double)len;
	i = 0;
	y = game->win_height / 2 - len / 2;
	if (y < 0)
		i = -y;
	ray->ty = ray->ratio * i;
	while (i < len - 1 && y + i < game->win_height)
	{
		ray->ty += ray->ratio;
		my_mlx_pixel_put(game, x, y + i,
			get_text_pixel(&ray->rtexture, ray->tx, ray->ty));
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
				my_mlx_pixel_put(game, j, i, 0x22222F);
			else
				my_mlx_pixel_put(game, j, i, 0x4a0904);
			j++;
		}
		i++;
	}
}

void	raycasting(t_game *game)
{
	int				nbr;
	t_raycasting	ray;

	draw_background(game);
	nbr = 0;
	ray.ra = fixang(game->player.pa + ((M_PI / 180) * 25));
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
		ray.col = create_vect(game->player.pos, ray.ra, ray.dist.x);
		ray.dist.x = ray.dist.x * cos(ray.ra - game->player.pa);
		draw_column(game, nbr, &ray);
		nbr++;
		ray.ra = fixang(ray.ra - ((M_PI / 180) * 50) / game->win_width);
	}
}
