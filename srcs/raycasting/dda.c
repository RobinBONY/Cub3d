/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:32:47 by rbony             #+#    #+#             */
/*   Updated: 2022/10/06 14:19:55 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static void	define_side(t_game *game, t_raycasting *ray)
{
	if (ray->ray_dir.dx < 0)
	{
		ray->step.x = -1;
		ray->side_dist.dx = (game->player.pos.x - ray->map_x)
			* ray->delta_dist.dx;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.dx = (ray->map_x + 1.0f - game->player.pos.x)
			* ray->delta_dist.dx;
	}
	if (ray->ray_dir.dy < 0)
	{
		ray->step.y = -1;
		ray->side_dist.dy = (game->player.pos.y - ray->map_y)
			* ray->delta_dist.dy;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.dy = (ray->map_y + 1.0f - game->player.pos.y)
			* ray->delta_dist.dy;
	}
}

static void	init_dda(t_game *game, t_raycasting *ray)
{
	if (ray->ray_dir.dx == 0.0f)
		ray->delta_dist.dx = 1e30;
	else
		ray->delta_dist.dx = fabs(1.0f / ray->ray_dir.dx);
	if (ray->ray_dir.dy == 0.0f)
		ray->delta_dist.dy = 1e30;
	else
		ray->delta_dist.dy = fabs(1.0f / ray->ray_dir.dy);
	define_side(game, ray);
}

static void	next_collision(t_raycasting *ray)
{
	if (ray->side_dist.dx < ray->side_dist.dy)
	{
		ray->side_dist.dx += ray->delta_dist.dx;
		ray->map_x += ray->step.x;
		ray->side_hit.x = ray->step.x;
		ray->side_hit.y = 0;
	}
	else
	{
		ray->side_dist.dy += ray->delta_dist.dy;
		ray->map_y += ray->step.y;
		ray->side_hit.y = ray->step.y;
		ray->side_hit.x = 0;
	}
}

static double	perp_dist(t_raycasting *ray)
{
	double	line;

	if (ray->side_hit.y == 0)
		line = ray->side_dist.dx - ray->delta_dist.dx;
	else
		line = ray->side_dist.dy - ray->delta_dist.dy;
	return (line);
}

void	dda(t_game *game, t_raycasting *ray)
{
	init_dda(game, ray);
	while (1)
	{
		next_collision(&ray);
		if (game->map[ray->map_y][ray->map_x] == 1)
		{
			ray->perp_dist = perp_dist(ray);
			if (ray->side_hit.x == 1)
				ray->side = 3;
			else if (ray->side_hit.x == -1)
				ray->side = 1;
			else if (ray->side_hit.y == 1)
				ray->side = 0;
			else
				ray->side = 2;
			return ;
		}
	}
	return ;
}
