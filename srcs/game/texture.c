/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:30:06 by rbony             #+#    #+#             */
/*   Updated: 2022/10/18 14:42:39 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	get_text_pixel(t_texture *texture, int x, int y)
{
	int	color;

	if (!texture)
		return (0);
	if (x < 0 || x > texture->width - 1 || y < 0 || y > texture->height - 1)
		return (0);
	color = (*(int *)(texture->text_address + (x * texture->bits_per_pixel / 8)
				+ (y * texture->line_length)));
	return (color);
}

int	store_textures_on_image(t_game *game, t_texture *texture,
	char *texture_path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, texture_path,
			&texture->width, &texture->height);
	if (texture->img == NULL)
		return (1);
	texture->text_address = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (texture->text_address == NULL)
	{
		if (access(texture_path, F_OK) == 0)
			return (1);
		else
			return (1);
	}
	return (0);
}
