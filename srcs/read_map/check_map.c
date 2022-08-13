/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:52:28 by alakhdar          #+#    #+#             */
/*   Updated: 2022/08/13 16:46:35 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

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
	game->map = (int **)malloc(sizeof(int *) * game->height);
	if (!game->map)
		return (1);
	while (i < game->height)
	{
		game->map[i] = malloc(sizeof(int) * game->width);
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

	game->height = 1;
	tmp = head;
	max_len = ft_strlen(tmp->content);
	if (check_closed_width(tmp->content))
		return (1);
	while (tmp->next != NULL)
	{
		if ((int)ft_strlen(tmp->content) > max_len)
			max_len = ft_strlen(tmp->content);
		if (check_closed_sides(tmp->content))
			return (1);
		tmp = tmp->next;
		game->height++;
	}
	if ((int)ft_strlen(tmp->content) > max_len)
			max_len = ft_strlen(tmp->content);
	if (check_closed_width(tmp->content))
		return (1);
	game->width = max_len;
	return (0);
}
