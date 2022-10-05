/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:32:49 by rbony             #+#    #+#             */
/*   Updated: 2022/10/05 14:27:01 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

double	fixang(double a)
{
	if (a >= ((double)2 * M_PI))
		a -= ((double)2 * M_PI);
	if (a < 0)
		a += ((double)2 * M_PI);
	return (a);
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

t_vector	init_vector(t_point start, t_point dest, double camera)
{
	t_vector	v;

	dprintf(2, "%f/n", camera);
	v.dx = (dest.x - start.x) + 0 * camera;
	v.dy = (dest.y - start.y) + 0.7 * camera;
	return (v);
}
