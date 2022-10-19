/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:39:47 by alakhdar          #+#    #+#             */
/*   Updated: 2022/10/18 14:40:23 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void move_forward(t_game *game)
{
	if (game->map[(int)game->player.pos.y / 64][(int)(game->player.pos.x + game->player.dir.x * 5) / 64] == 0)
		game->player.pos.x += game->player.dir.x * 5;
	if (game->map[(int)(game->player.pos.y + game->player.dir.y * 5) / 64][(int)game->player.pos.x / 64] == 0)
		game->player.pos.y += game->player.dir.y * 5;
}

void move_backward(t_game *game)
{
	if (game->map[(int)game->player.pos.y / 64][(int)(game->player.pos.x - game->player.dir.x * 5) / 64] == 0)
		game->player.pos.x -= game->player.dir.x * 5;
	if (game->map[(int)(game->player.pos.y - game->player.dir.y * 5) / 64][(int)game->player.pos.x / 64] == 0)
		game->player.pos.y -= game->player.dir.y * 5;
}

void rotate_right(t_game *game)
{
	game->player.pa -= (M_PI / 180) * 3;
	game->player.pa = fixang(game->player.pa);
	game->player.dir.x = cos(game->player.pa);
	game->player.dir.y = -sin(game->player.pa);
}

void rotate_left(t_game *game)
{
	game->player.pa += (M_PI / 180) * 3;
	game->player.pa = fixang(game->player.pa);
	game->player.dir.x = cos(game->player.pa);
	game->player.dir.y = -sin(game->player.pa);
}
