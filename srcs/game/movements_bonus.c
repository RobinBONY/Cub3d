/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:39:47 by alakhdar          #+#    #+#             */
/*   Updated: 2022/10/19 13:37:42 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	move_forward(t_game *game)
{
	if (in_map(game, (int)(game->player.pos.x + game->player.dir.x * 5) / 64,
		(int)game->player.pos.y / 64)
		&& game->map[(int)game->player.pos.y / 64]
		[(int)(game->player.pos.x + game->player.dir.x * 5) / 64] == 0)
		game->player.pos.x += game->player.dir.x * 5;
	if (in_map(game, (int)game->player.pos.x / 64,
			(int)(game->player.pos.y + game->player.dir.y * 5) / 64)
		&& game->map[(int)(game->player.pos.y + game->player.dir.y * 5) / 64]
		[(int)game->player.pos.x / 64] == 0)
		game->player.pos.y += game->player.dir.y * 5;
}

void	move_backward(t_game *game)
{
	if (in_map(game, (int)(game->player.pos.x - game->player.dir.x * 5) / 64,
		(int)game->player.pos.y / 64)
		&& game->map[(int)game->player.pos.y / 64]
		[(int)(game->player.pos.x - game->player.dir.x * 5) / 64] == 0)
		game->player.pos.x -= game->player.dir.x * 5;
	if (in_map(game, (int)game->player.pos.x / 64,
			(int)(game->player.pos.y - game->player.dir.y * 5) / 64)
		&& game->map[(int)(game->player.pos.y - game->player.dir.y * 5) / 64]
		[(int)game->player.pos.x / 64] == 0)
		game->player.pos.y -= game->player.dir.y * 5;
}

void	move_left(t_game *game)
{
	t_point	left_dir;

	left_dir.x = cos(game->player.pa + (M_PI / 2));
	left_dir.y = -sin(game->player.pa + (M_PI / 2));
	if (in_map(game, (int)(game->player.pos.x + left_dir.x * 5) / 64,
		(int)game->player.pos.y / 64)
		&& game->map[(int)game->player.pos.y / 64]
		[(int)(game->player.pos.x + left_dir.x * 5) / 64] == 0)
		game->player.pos.x += left_dir.x * 5;
	if (in_map(game, (int)game->player.pos.x / 64,
			(int)(game->player.pos.y + left_dir.y * 5) / 64)
		&& game->map[(int)(game->player.pos.y + left_dir.y * 5) / 64]
		[(int)game->player.pos.x / 64] == 0)
		game->player.pos.y += left_dir.y * 5;
}

void	move_right(t_game *game)
{
	t_point	right_dir;

	right_dir.x = cos(game->player.pa + (M_PI / 2));
	right_dir.y = -sin(game->player.pa + (M_PI / 2));
	if (in_map(game, (int)(game->player.pos.x - right_dir.x * 5) / 64,
		(int)game->player.pos.y / 64)
		&& game->map[(int)game->player.pos.y / 64]
		[(int)(game->player.pos.x - right_dir.x * 5) / 64] == 0)
		game->player.pos.x -= right_dir.x * 5;
	if (in_map(game, (int)game->player.pos.x / 64,
			(int)(game->player.pos.y - right_dir.y * 5) / 64)
		&& game->map[(int)(game->player.pos.y - right_dir.y * 5) / 64]
		[(int)game->player.pos.x / 64] == 0)
		game->player.pos.y -= right_dir.y * 5;
}
