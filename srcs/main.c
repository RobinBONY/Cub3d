/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:38:45 by rbony             #+#    #+#             */
/*   Updated: 2022/10/06 15:24:33 by rbony            ###   ########lyon.fr   */
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

t_point	check_move(t_game *game, t_point new_pos)
{
	if (game->map[(int)(new_pos.y)][(int)(new_pos.x)] == 1)
		return (game->player);
	return (new_pos);
}

int	manage_events(int keycode, t_game *game)
{
	if (keycode == 65307 || keycode == 53)
		close_window(game);
	if (keycode == 13)
		game->player = game->player; //move forward
	if (keycode == 1)
		game->player = game->player; //move backward
	if (keycode == 2)
		game->pa = fixang(game->pa - M_PI / 50);
	if (keycode == 0)
		game->pa = fixang(game->pa + M_PI / 50);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	init(t_game *game)
{
	game->win_width = 1920;
	game->win_height = 1080;
	game->player.pos.x = 7.5;
	game->player.pos.y = 3.5;
	game->player.dir.dx = -1;
	game->player.dir.dy = 0;
	game->plane.x = 0;
	game->plane.y = 0.7;
	game->time = 0;
	game->old_time = 0;
	gettimeofday(&game->start, NULL);
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
		raycasting(&game);
		mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
		mlx_hook(game.win, 17, 1L << 0, close_window, &game);
		mlx_hook(game.win, 02, 1L << 0, manage_events, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
