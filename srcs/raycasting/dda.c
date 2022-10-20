/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:02:29 by alakhdar          #+#    #+#             */
/*   Updated: 2022/10/20 15:32:43 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	calculate_tx(t_raycasting *ray)
{
	if (ray->hcolor % 2 == 0)
		ray->tx = ((ray->col.x / 64.0f) - (int)(ray->col.x / 64.0f))
			* ray->rtexture.width;
	else
		ray->tx = ((ray->col.y / 64.0f) - (int)(ray->col.y / 64.0f))
			* ray->rtexture.width;
	if (ray->hcolor == 3 || ray->hcolor == 4)
		ray->tx = ray->rtexture.width - ray->tx;
}

void	check_vertical(t_game *game, t_raycasting *ray)
{
	ray->rtan = tan(ray->ra);
	if (cos(ray->ra) > 0.001)
		vert_facing_left(game, ray);
	else if (cos(ray->ra) < -0.001)
		vert_facing_right(game, ray);
	else
		vert_up_down(game, ray);
	while (ray->dof < 100)
	{
		ray->map_x = (int)(ray->ray.x) >> 6;
		ray->map_y = (int)(ray->ray.y) >> 6;
		if (in_map(game, ray->map_x, ray->map_y)
			&& game->map[ray->map_y][ray->map_x] == 1)
			get_disty(game, ray);
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
		hori_facing_up(game, ray);
	else if (sin(ray->ra) < -0.001)
		hori_facing_down(game, ray);
	else
		vert_facing_rl(game, ray);
	while (ray->dof < 100)
	{
		ray->map_x = (int)(ray->ray.x) >> 6;
		ray->map_y = (int)(ray->ray.y) >> 6;
		if (in_map(game, ray->map_x, ray->map_y)
			&& game->map[ray->map_y][ray->map_x] == 1)
		{
			ray->dof = 100;
			ray->dist.x = cos(ray->ra) * (ray->ray.x - game->player.pos.x)
				- sin(ray->ra) * (ray->ray.y - game->player.pos.y);
		}
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
