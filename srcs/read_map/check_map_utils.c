/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:44:43 by alakhdar          #+#    #+#             */
/*   Updated: 2022/08/15 13:22:29 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	ft_isspace(int c)
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
	while (h < game->map_height)
	{
		i = 0;
		while (i < game->map_width)
		{
			if (i < (int)ft_strlen(tmp->content) && tmp->content[i] - '0' >= 0)
				game->map[h][i] = tmp->content[i] - '0';
			else
				game->map[h][i] = -1;
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
		if (str[i] != '1' && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_closed_width(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_closed_sides(char *str)
{
	int		i;

	i = 0;
	if (str[i] != '1')
		if (!ft_isspace(str[i]))
			return (1);
	while (str[i] && str[i + 1])
	{
		if (ft_isspace(str[i]) && str[i + 1] == '0')
			return (1);
		if (str[i] == '0' && ft_isspace(str[i + 1]))
			return (1);
		i++;
	}
	if (str[i] != '1')
		if (!ft_isspace(str[i]))
			return (1);
	return (0);
}
