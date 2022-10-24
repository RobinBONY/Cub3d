/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:34:21 by alakhdar          #+#    #+#             */
/*   Updated: 2022/10/20 15:28:45 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	check_text_db(t_game *game)
{
	return (game->map_info.n_texture.img
		&& game->map_info.e_texture.img
		&& game->map_info.s_texture.img
		&& game->map_info.w_texture.img);
}

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

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
