/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:57:02 by rbony             #+#    #+#             */
/*   Updated: 2022/10/19 13:58:14 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	print_menu(t_game *data)
{
	char	*fps;

	fps = ft_itoa(data->frametime);
	mlx_string_put(data->mlx, data->win,
		85, 20, 0xEF8633, "COMMANDS");
	mlx_string_put(data->mlx, data->win,
		85, 40, 0xEAEAEA, "Move: W / A / S / D");
	mlx_string_put(data->mlx, data->win, 85,
		60, 0xEAEAEA, "Rotate: <- / ->");
	mlx_string_put(data->mlx, data->win, 85,
		80, 0xEAEAEA, "FPS: ");
	mlx_string_put(data->mlx, data->win, 125,
		80, 0xEAEAEA, fps);
	free(fps);
}

int	close_window(t_game *game)
{
	int	i;

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

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307 || keycode == 53)
		close_window(game);
	else if (keycode < 200)
		game->keyboard[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode < 200)
		game->keyboard[keycode] = 0;
	return (1);
}

int	manage_events(t_game *game)
{
	if (game->keyboard[13])
		move_forward(game);
	if (game->keyboard[1])
		move_backward(game);
	if (game->keyboard[0])
		move_left(game);
	if (game->keyboard[2])
		move_right(game);
	if (game->keyboard[124])
		rotate_right(game);
	if (game->keyboard[123])
		rotate_left(game);
	game->old_time = game->time;
	game->time = get_timestamp(game->start);
	game->frametime = 1 / (game->time - game->old_time);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	print_menu(game);
	return (0);
}
