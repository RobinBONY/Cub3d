/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:52:28 by alakhdar          #+#    #+#             */
/*   Updated: 2022/08/15 13:22:10 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	check_valid_cells(int **map, t_game *game, int i, int j)
{
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (map[i][j] == 0)
			{
				if (((j > 0 && map[i][j - 1] != 0)
					&& (j > 0 && map[i][j - 1] != 1))
					|| ((j < game->map_width && map[i][j + 1] != 0)
					&& (j < game->map_width && map[i][j + 1] != 1)))
					return (1);
				if (((i > 0 && map[i - 1][j] != 0)
					&& (i > 0 && map[i - 1][j] != 1))
					|| ((i < game->map_height && map[i + 1][j] != 0)
					&& (i < game->map_height && map[i + 1][j] != 1)))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_ext(char *str, char *ext)
{
	char	*tmp;

	tmp = ft_strstr(str, ext);
	if (!tmp)
		return (0);
	if (ft_strcmp(tmp, ext))
		return (0);
	return (1);
}

int	create_int_map(t_game *game, t_list *list)
{
	int		i;

	i = 0;
	game->map = (int **)malloc(sizeof(int *) * game->map_height);
	if (!game->map)
		return (1);
	while (i < game->map_height)
	{
		game->map[i] = malloc(sizeof(int) * game->map_width);
		if (!game->map[i])
			return (1);
		i++;
	}
	fill_int_map(game, list);
	return (0);
}

int	check_map_layout(t_list *head, t_game *game)
{
	t_list	*tmp;
	int		max_len;

	game->map_height = 1;
	tmp = head;
	max_len = ft_strlen(tmp->content);
	if (check_closed_width(tmp->content))
		return (1);
	while (tmp->next != NULL)
	{
		if ((int)ft_strlen(tmp->content) > max_len)
			max_len = ft_strlen(tmp->content);
		tmp = tmp->next;
		game->map_height++;
	}
	if (check_closed_width(tmp->content))
		return (1);
	if ((int)ft_strlen(tmp->content) > max_len)
			max_len = ft_strlen(tmp->content);
	game->map_width = max_len;
	return (0);
}
