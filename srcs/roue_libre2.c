/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roue_libre2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:26:50 by rbony             #+#    #+#             */
/*   Updated: 2022/10/05 14:26:52 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	draw_square(t_game *game, int x, int y)
{
	int				width;
	int				i;

	width = 0;
	while (width < 63)
	{
		i = 0;
		while (i < 63)
		{
			my_mlx_pixel_put(game, x + i, y + width, 0xFF0000);
			i++;
		}
		width++;
	}
}

void	brest(t_game *env, int sx, int sy, int ex, int ey)
{
	double	i;
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
				draw_square(game, j * 64, i * 64);
			j++;
		}
		i++;
	}
}
