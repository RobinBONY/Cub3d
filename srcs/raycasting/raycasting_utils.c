/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:32:49 by rbony             #+#    #+#             */
/*   Updated: 2022/09/19 15:55:54 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

float	fixang(float a)
{
	if (a >= ((float)2 * M_PI))
		a -= ((float)2 * M_PI);
	if (a < 0)
		a += ((float)2 * M_PI);
	return (a);
}

int	in_map(t_game *game, int x, int y)
{
	if (x > 0 && y > 0 && x < game->map_width && y < game->map_height)
		return (1);
	return (0);
}

t_point	create_vect(t_point origin, float radian, float length)
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
