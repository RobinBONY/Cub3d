/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:38:45 by rbony             #+#    #+#             */
/*   Updated: 2022/08/15 18:22:12 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static int	close_window(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	close(game->textures.n_texture);
	close(game->textures.s_texture);
	close(game->textures.e_texture);
	close(game->textures.w_texture);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

int	manage_events(int keycode, t_game *game)
{
	printf("%d\n", keycode);
	if (keycode == 65307 || keycode == 53)
		close_window(game);
	return (0);
}

void	init(t_game *game)
{
	game->win_width = 1920;
	game->win_height = 1080;
	game->player.px = 8 * 64;
	game->player.py = 4 * 64;
	game->player.pa = 180;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2 && !read_map(&game, argv[1]))
	{
		init(&game);
		game.mlx = mlx_init();
		game.win = mlx_new_window(game.mlx, game.win_width,
				game.win_height, "Cub3D");
		game.img.img = mlx_new_image(game.mlx, 1920, 1080);
		game.img.addr = mlx_get_data_addr(game.img.img,
				&game.img.bits_per_pixel, &game.img.line_length,
				&game.img.endian);
		draw(&game);
		mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
		mlx_hook(game.win, 17, 1L << 0, close_window, &game);
		mlx_hook(game.win, 02, 1L << 0, manage_events, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
