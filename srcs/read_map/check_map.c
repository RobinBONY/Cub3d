/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:52:28 by alakhdar          #+#    #+#             */
/*   Updated: 2022/08/11 16:29:31 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	check_ext(char *str)
{
	char	*tmp;

	tmp = ft_strstr(str, ".cub");
	if (!tmp)
		return (0);
	if (ft_strcmp(tmp, ".cub"))
		return (0);
	return (1);
}

int	create_int_map(t_game *game, t_list *list)
{
	int		i;

	i = 0;
	game->map = (int **)malloc(sizeof(int *) * game->height);
	if (!game->map)
		return (-1);
	while (i < game->height)
	{
		game->map[i] = malloc(sizeof(int) * game->width);
		if (!game->map[i])
			return (-1);
		i++;
	}
	fill_int_map(game, list);
	return (1);
}

int	check_map_layout(t_list *head, t_game *game)
{
	t_list	*tmp;
	int		max_len;
	int		tmp_len;

	game->height = 1;
	tmp = head;
	max_len = ft_strlen(tmp->content);
	if (check_closed_width(tmp->content) != 1)
		return (0);
	while (tmp->next != NULL)
	{
		tmp_len = ft_strlen(tmp->content);
		if (tmp_len > max_len)
			max_len = tmp_len;
		if (check_closed_sides(tmp->content) != 1)
			return (0);
		tmp = tmp->next;
		game->height++;
	}
	tmp_len = ft_strlen(tmp->content);
	if (tmp_len > max_len)
			max_len = tmp_len;
	if (check_closed_width(tmp->content) != 1)
		return (0);
	game->width = max_len;
	return (1);
}
