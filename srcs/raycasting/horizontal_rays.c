/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:57:28 by alakhdar          #+#    #+#             */
/*   Updated: 2022/10/18 15:01:09 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	hori_facing_up(t_game *game, t_raycasting *ray)
{
	ray->ray.y = (((int)game->player.pos.y >> 6) << 6) - 0.0001;
	ray->ray.x = (game->player.pos.y - ray->ray.y)
		* ray->rtan + game->player.pos.x;
	ray->o.y = -64;
	ray->o.x = -ray->o.y * ray->rtan;
	ray->hcolor = 2;
}

void	hori_facing_down(t_game *game, t_raycasting *ray)
{
	ray->ray.y = (((int)game->player.pos.y >> 6) << 6) + 64;
	ray->ray.x = (game->player.pos.y - ray->ray.y)
		* ray->rtan + game->player.pos.x;
	ray->o.y = 64;
	ray->o.x = -ray->o.y * ray->rtan;
	ray->hcolor = 4;
}

void	vert_facing_rl(t_game *game, t_raycasting *ray)
{
	ray->ray.x = game->player.pos.x;
	ray->ray.y = game->player.pos.y;
	ray->dof = 100;
}
