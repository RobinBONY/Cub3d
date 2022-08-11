/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:44:43 by alakhdar          #+#    #+#             */
/*   Updated: 2022/08/11 16:14:37 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_isspace(int c)
{
	if (c && (c == 32 || c == 9
			|| c == 10 || c == 11
			|| c == 12 || c == 13))
	{
		return (1);
	}
	return (0);
}

void	fill_int_map(t_game *game, t_list *list)
{
	t_list	*tmp;
	int		h;
	int		i;

	h = 0;
	tmp = list;
	while (h < game->height)
	{
		i = 0;
		while (i < width)
		{
			tmp->map[h][i] = ft_atoi(tmp->content[i]);
			i++;
		}
		h++;
		tmp = tmp->next;
	}
}

int	check_closed_width(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != "1")
			return (0);
		i++;
	}
	return (1);
}

int	check_closed_sides(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (!ft_isspace(str[i]) && str[i + 1] == "0")
			return (0);
		if (str[i] == "0" && !ft_isspace(str[i + 1]))
			return (0);
		i++;
	}
	return (1);
}
