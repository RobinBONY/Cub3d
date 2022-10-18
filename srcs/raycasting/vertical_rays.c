/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:47:53 by alakhdar          #+#    #+#             */
/*   Updated: 2022/10/18 14:56:28 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	vert_facing_left(t_game *game, t_raycasting *ray)
{
	ray->ray.x = (((int)game->player.pos.x >> 6) << 6) + 64;
	ray->ray.y = (game->player.pos.x - ray->ray.x)
		* ray->rtan + game->player.pos.y;
	ray->o.x = 64;
	ray->o.y = -ray->o.x * ray->rtan;
	ray->vcolor = 1;
}

void	vert_facing_right(t_game *game, t_raycasting *ray)
{
	ray->ray.x = (((int)game->player.pos.x >> 6) << 6) - 0.0001;
	ray->ray.y = (game->player.pos.x - ray->ray.x)
		* ray->rtan + game->player.pos.y;
	ray->o.x = -64;
	ray->o.y = -ray->o.x * ray->rtan;
	ray->vcolor = 3;
}

void	vert_up_down(t_game *game, t_raycasting *ray)
{
	ray->ray.x = game->player.pos.x;
	ray->ray.y = game->player.pos.y;
	ray->dof = 100;
}

void	get_disty(t_game *game, t_raycasting *ray)
{
	ray->dof = 100;
	ray->dist.y = cos(ray->ra) * (ray->ray.x - game->player.pos.x)
		- sin(ray->ra) * (ray->ray.y - game->player.pos.y);
}
