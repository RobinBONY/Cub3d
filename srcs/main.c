/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:38:45 by rbony             #+#    #+#             */
/*   Updated: 2022/10/13 10:35:05 by rbony            ###   ########lyon.fr   */
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

void	move_forward(t_game *game)
{
	if (game->map[(int)game->player.pos.y / 64][(int)(game->player.pos.x + game->player.dir.x * 5) / 64] == 0)
		game->player.pos.x += game->player.dir.x * 5;
	if (game->map[(int)(game->player.pos.y + game->player.dir.y * 5) / 64][(int)game->player.pos.x / 64] == 0)
		game->player.pos.y += game->player.dir.y * 5;
}

void	move_backward(t_game *game)
{
	if (game->map[(int)game->player.pos.y / 64][(int)(game->player.pos.x - game->player.dir.x * 5) / 64] == 0)
		game->player.pos.x -= game->player.dir.x * 5;
	if (game->map[(int)(game->player.pos.y - game->player.dir.y * 5) / 64][(int)game->player.pos.x / 64] == 0)
		game->player.pos.y -= game->player.dir.y * 5;
}

void	rotate_right(t_game *game)
{
	game->player.pa -= (M_PI / 180) * 5;
	game->player.pa = fixang(game->player.pa);
	game->player.dir.x = cos(game->player.pa);
	game->player.dir.y = -sin(game->player.pa);
}

void	rotate_left(t_game *game)
{
	game->player.pa += (M_PI / 180) * 5;
	game->player.pa = fixang(game->player.pa);
	game->player.dir.x = cos(game->player.pa);
	game->player.dir.y = -sin(game->player.pa);
}

int	manage_events(int keycode, t_game *game)
{
	dprintf(2, "%d\n", keycode);
	if (keycode == 65307 || keycode == 53)
		close_window(game);
	if (keycode == 13 || keycode == 122)
		move_forward(game);
	if (keycode == 1  || keycode == 115)
		move_backward(game);
	if (keycode == 2  || keycode == 100)
		rotate_right(game);
	if (keycode == 0  || keycode == 113)
		rotate_left(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	init(t_game *game)
{
	game->win_width = 1920;
	game->win_height = 1080;
	game->player.pos.x = 3.5 * 64;
	game->player.pos.y = 10.5 * 64;
	game->player.pa = 0;
	game->player.dir.x = cos(game->player.pa);
	game->player.dir.y = -sin(game->player.pa);
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
