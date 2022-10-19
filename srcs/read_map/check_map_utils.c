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

int	fill_player_pos(t_game *game, char *dir, int x, int y)
{
	if (game->player.pos.x == 0 && game->player.pos.y == 0)
	{
		game->player.pos.x = x * 64 + 32;
		game->player.pos.y = y * 64 + 32;
		if (*dir == 'N')
			game->player.pa = M_PI / 2;
		if (*dir == 'E')
			game->player.pa = 0;
		if (*dir == 'S')
			game->player.pa = (3 * M_PI) / 2;
		if (*dir == 'W')
			game->player.pa = M_PI;
		game->player.dir.x = cos(game->player.pa);
		game->player.dir.y = -sin(game->player.pa);
		*dir = '0';
	}
	else
		return (1);
	return (0);
}

int	fill_int_map(t_game *game, t_list *tmp)
{
	int		h;
	int		i;

	h = 0;
	while (h < game->map_height)
	{
		i = 0;
		while (i < game->map_width)
		{
			if (i < (int)ft_strlen(tmp->content) && tmp->content[i] - '0' >= 0)
			{
				if (tmp->content[i] == 'N' || tmp->content[i] == 'E'
					|| tmp->content[i] == 'S' || tmp->content[i] == 'W')
					if (fill_player_pos(game, &tmp->content[i], i, h))
						return (1);
				game->map[h][i] = tmp->content[i] - '0';
			}
			else
				game->map[h][i] = -1;
			i++;
		}
		h++;
		tmp = tmp->next;
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
