/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roue_libre.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 09:00:28 by rbony             #+#    #+#             */
/*   Updated: 2022/08/13 14:48:53 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	error_1(char *str)
{
	printf("%s %s\n", ERROR, str);
	return (1);
}

int	error_2(char *str1, char *str2)
{
	printf("%s %s %s\n", ERROR, str1, str2);
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	split_size(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

int	check_texture(t_game *game, t_texture *texture, char **filename)
{
	int	file_exists;

	file_exists = access(filename[1], R_OK);
	if (check_ext(filename[1], ".xpm") && file_exists == 0)
	{
		store_textures_on_image(game, texture, filename[1]);
		if (!texture)
			return (error_2(filename[0], READING_FILE));
		return (0);
	}
	if (file_exists == -1)
	{
		if (access(filename[1], F_OK) == 0)
			return (error_2(filename[0], PD));
		else
			return (error_2(filename[0], TEXTURE_NF));
	}
	return (error_2(filename[0], INVALID_FORMAT));
}

int	check_color(t_color *color, char **filename)
{
	char	**color_split;

	color_split = ft_split(filename[1], ',');
	if (!color_split)
		return (error_2(filename[0], READING_FILE));
	if (split_size(color_split) == 3)
	{
		color->r = ft_atoi(color_split[0]);
		color->g = ft_atoi(color_split[1]);
		color->b = ft_atoi(color_split[2]);
		free_split(color_split);
		return (0);
	}
	free_split(color_split);
	return (error_2(filename[0], COLOR_INVALID));
}

int	find_keyword(t_game *game, char **line)
{
	if (ft_strcmp(line[0], "NO") == 0)
		return (check_texture(game, &game->map_info.n_texture, line));
	if (ft_strcmp(line[0], "SO") == 0)
		return (check_texture(game, &game->map_info.s_texture, line));
	if (ft_strcmp(line[0], "EA") == 0)
		return (check_texture(game, &game->map_info.e_texture, line));
	if (ft_strcmp(line[0], "WE") == 0)
		return (check_texture(game, &game->map_info.w_texture, line));
	if (ft_strcmp(line[0], "F") == 0)
		return (check_color(&game->map_info.f_color, line));
	if (ft_strcmp(line[0], "C") == 0)
		return (check_color(&game->map_info.c_color, line));
	return (error_1(INVALID_FORMAT));
}

int	parse_textures(t_game *game, t_list **list)
{
	int		i;
	char	**split;

	i = 0;
	while (i < 6 && *list)
	{
		split = ft_split((*list)->content, ' ');
		if (!split)
			return (error_1(READING_FILE));
		if (find_keyword(game, split))
		{
			free_split(split);
			return (1);
		}
		i++;
		*list = (*list)->next;
		free_split(split);
	}
	return (0);
}
