/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:32:47 by rbony             #+#    #+#             */
/*   Updated: 2022/100/11 11:16:52 by rbony            ###   ########lray->o.yn.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	check_vertical(t_game *game, t_raycasting *ray)
{
	ray->rtan = tan(ray->ra);
	if (cos(ray->ra) > 0.001)
	{
		ray->ray.x = (((int)game->player.pos.x >> 6) << 6) + 64;
		ray->ray.y = (game->player.pos.x - ray->ray.x) * ray->rtan + game->player.pos.y;
		ray->o.x = 64;
		ray->o.y = -ray->o.x * ray->rtan;
		ray->vcolor = 1;
	}//looking left
	else if (cos(ray->ra) < -0.001)
	{
		ray->ray.x = (((int)game->player.pos.x >> 6) << 6) - 0.0001;
		ray->ray.y = (game->player.pos.x - ray->ray.x) * ray->rtan + game->player.pos.y;
		ray->o.x = -64;
		ray->o.y = -ray->o.x * ray->rtan;
		ray->vcolor = 3;
	}//looking right
	else
	{
		ray->ray.x = game->player.pos.x;
		ray->ray.y = game->player.pos.y;
		ray->dof = 100;
	}//looking up or down. no hit
	while (ray->dof < 100)
	{
		ray->map_x = (int)(ray->ray.x) >> 6;
		ray->map_y = (int)(ray->ray.y) >> 6;
		if (in_map(game, ray->map_x, ray->map_y) && game->map[ray->map_y][ray->map_x] == 1)
		{
			ray->dof = 100;
			ray->dist.y = cos(ray->ra) * (ray->ray.x - game->player.pos.x) - sin(ray->ra) * (ray->ray.y - game->player.pos.y);
		}
		else
		{
			ray->ray.x += ray->o.x;
			ray->ray.y += ray->o.y;
			ray->dof += 1;
		}
	}
	ray->vertical.x = ray->ray.x;
	ray->vertical.y = ray->ray.y;
}

void	check_horizontal(t_game *game, t_raycasting *ray)
{
	ray->rtan = 1.0 / ray->rtan;
	if (sin(ray->ra) > 0.001)
	{
		ray->ray.y = (((int)game->player.pos.y >> 6) << 6) - 0.0001;
		ray->ray.x = (game->player.pos.y - ray->ray.y) * ray->rtan + game->player.pos.x;
		ray->o.y = -64;
		ray->o.x = -ray->o.y * ray->rtan;
		ray->hcolor = 2;
	}//looking up
	else if (sin(ray->ra) < -0.001)
	{
		ray->ray.y = (((int)game->player.pos.y >> 6) << 6) + 64;
		ray->ray.x = (game->player.pos.y - ray->ray.y) * ray->rtan + game->player.pos.x;
		ray->o.y = 64;
		ray->o.x = -ray->o.y * ray->rtan;
		ray->hcolor = 4;
	}//looking down
	else
	{
		ray->ray.x = game->player.pos.x;
		ray->ray.y = game->player.pos.y;
		ray->dof = 100;
	}//looking straight left or right
	while (ray->dof < 100)
	{
		ray->map_x = (int)(ray->ray.x) >> 6;
		ray->map_y = (int)(ray->ray.y) >> 6;
		if (in_map(game, ray->map_x, ray->map_y) && game->map[ray->map_y][ray->map_x] == 1)
		{
			ray->dof = 100;
			ray->dist.x = cos(ray->ra) * (ray->ray.x - game->player.pos.x) - sin(ray->ra) * (ray->ray.y - game->player.pos.y);
		}//hit
		else
		{
			ray->ray.x += ray->o.x;
			ray->ray.y += ray->o.y;
			ray->dof += 1;
		}
	}
}

void	dda(t_game *game, t_raycasting *ray)
{
	ray->dof = 0;
	ray->vcolor = 0;
	ray->hcolor = 0;
	ray->dist.y = 1000000;
	check_vertical(game, ray);
	ray->dof = 0;
	ray->dist.x = 1000000;
	check_horizontal(game, ray);
}
