/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:38:45 by rbony             #+#    #+#             */
/*   Updated: 2022/10/19 13:57:31 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	init(t_game *game, char *argv)
{
	game->win_width = 2048;
	game->win_height = 1024;
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	ft_memset(game->keyboard, 0, 200);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, game->win_width,
			game->win_height, "Cub3D");
	if (!game->win)
		return (1);
	game->img.img = mlx_new_image(game->mlx, game->win_width,
			game->win_height);
	if (!game->img.img)
		return (1);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		return (1);
	if (read_map(game, argv))
		return (1);
	gettimeofday(&game->start, NULL);
	game->time = get_timestamp(game->start);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		if (init(&game, argv[1]))
			return (0);
		mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 17, 1L << 0, close_window, &game);
		mlx_loop_hook(game.mlx, manage_events, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
