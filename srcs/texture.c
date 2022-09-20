/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:15:06 by alakhdar          #+#    #+#             */
/*   Updated: 2022/09/20 14:18:14 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	get_text_pix(t_texture *texture, int x, int y)
{
	int	color;

	if (texture == NULL)
	{
		return (0);
	}
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
	{
		return (0);
	}
	color = (*(int *)(texture->img + (x * texture->bits_per_pixel / 8)
				+ (y * texture->line_length)));
	return (color);
}

int	store_textures_on_image(t_game *game, t_texture *texture, char *texture_path)
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

int	init_textures(t_game *game)
{
	int	error;

	error = 0;
	game->textures = malloc(sizeof(t_texture) * 4);
	if (game->textures == NULL)
		return (1);
	error |= store_textures_on_image(game, &game->textures[0], &game->texture_name[0]);
	error |= store_textures_on_image(game, &game->textures[1], &game->texture_name[1]);
	error |= store_textures_on_image(game, &game->textures[2], &game->texture_name[2]);
	error |= store_textures_on_image(game, &game->textures[3], &game->texture_name[3]);
	if (error == 1)
		dprintf(2, "Error while loading textures.\n");
	return (error);
}

//perpWallDist = rayon du rayon perpendiculaire
//sideDistX = 
/*void	calculate_stripe(t_raycasting *raycasting, t_game *game)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	//On print slice par slice (En vertical sur une coordonnée X, sur toute la hauteur de la slice)
	if (ray->side == 0)
		perpWallDist = (sideDistX - deltaDistX);
	else
		perpWallDist = (sideDistY - deltaDistY);
	line_height = (int)(game->height / perpWallDist);
	draw_start = -line_height / 2 + game->height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->height / 2;
	if (draw_end >= game->height)
		draw_end = game->height - 1;
	//return (draw_start/draw_end/line_height)
}

double	calculate_texturing(t_raycasting *raycasting, t_textures *texture)
{
	double	wallx;
	int		texx;

	//Valeur exacte où le rayon touche le mur
	if (ray->side == 0)
		wallx = pos_y + perpWallDist * ray_diry;
	else
		wallx = pos_x + perpendiculaire * ray_dirx;
	wallx -= floor(wallx);
	texx = (int)(wallx * double (texture->width));
	//Coordonnée X sur la texture
	if (ray->side == 0 && ray_dirx > 0)
		texx = texture->width - texx -1;
	if (ray->side == 1 && ray_diry < 0)
		texx = texture->width - texx -1;
}

void	draw_textured_stripe(t_game *game, t_texture texture)
{
	double	step;
	double	tex_pos;
	int		color;
	int		i;
	int		texy;

	i = draw_start;
	step = 1.0 * texture->height / line_height;
	tex_pos = (draw_start - game->height / 2 + line_height / 2) * step;
	while (i < draw_end)
	{
		texy = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = get_text_pixel()
		if (game->side == 1)
			color = (color >> 1) & 8355711;
		i++;
	}
}
*/