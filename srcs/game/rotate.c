/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:37:23 by rbony             #+#    #+#             */
/*   Updated: 2022/10/19 13:37:44 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	rotate_right(t_game *game)
{
	game->player.pa -= (M_PI / 180) * 3;
	game->player.pa = fixang(game->player.pa);
	game->player.dir.x = cos(game->player.pa);
	game->player.dir.y = -sin(game->player.pa);
}

void	rotate_left(t_game *game)
{
	game->player.pa += (M_PI / 180) * 3;
	game->player.pa = fixang(game->player.pa);
	game->player.dir.x = cos(game->player.pa);
	game->player.dir.y = -sin(game->player.pa);
}
