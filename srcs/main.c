/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:38:45 by rbony             #+#    #+#             */
/*   Updated: 2022/10/18 15:44:30 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int key_press(int keycode, t_game *game)
{
	if (keycode == 65307 || keycode == 53)
		close_window(game);
	else if (keycode < 200)
		game->keyboard[keycode] = 1;
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode < 200)
		game->keyboard[keycode] = 0;
	return (1);
}

static int close_window(t_game *game)
{
	int i;

	i = 0;
	while (i < game->map_height)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

int manage_events(t_game *game)
{
	if (game->keyboard[13] || game->keyboard[122])
		move_forward(game);
	if (game->keyboard[1] || game->keyboard[115])
		move_backward(game);
	if (game->keyboard[2] || game->keyboard[100])
		rotate_right(game);
	if (game->keyboard[0] || game->keyboard[113])
		rotate_left(game);
	// fps counter
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	// print fps
	return (0);
}

int init(t_game *game)
{
	game->win_width = 2048;
	game->win_height = 1024;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game.mlx, game.win_width,
							   game.win_height, "Cub3D");
	if (!game->win)
		return (1);
	game->img.img = mlx_new_image(game.mlx, 2048, 1024);
	if (!game->img.img)
		return (1);
	game->img.addr = mlx_get_data_addr(game.img.img,
									   &game.img.bits_per_pixel, &game.img.line_length,
									   &game.img.endian);
	if (!game->img.addr)
		return (1);
	if (read_map(&game, argv[1]))
		return (1);
	gettimeofday(&game->start, NULL);
	return (0);
}

int main(int argc, char **argv)
{
	t_game game;

	if (argc == 2)
	{
		if (init(&game))
			return (0);
		// raycasting(&game);
		mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 17, 1L << 0, close_window, &game);
		mlx_loop_hook(game.mlx, manage_events, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
