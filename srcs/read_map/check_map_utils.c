/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:44:43 by alakhdar          #+#    #+#             */
/*   Updated: 2022/08/13 16:50:35 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

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

/*Debug functions*/

void	print_data(t_game *game)
{
	int	i;
	int	j;

	printf("n texture : %d\n", game->textures.n_texture);
	printf("s texture : %d\n", game->textures.s_texture);
	printf("e texture : %d\n", game->textures.e_texture);
	printf("w texture : %d\n", game->textures.w_texture);
	printf("f color : %d,%d,%d\n", game->textures.f_color.r, game->textures.f_color.g, game->textures.f_color.b);
	printf("c color : %d,%d,%d\n", game->textures.c_color.r, game->textures.c_color.g, game->textures.c_color.b);
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			printf("%d\t", game->map[i][j]);
			j++;
		}
		printf("%c", '\n');
		i++;
	}
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
		while (i < game->width)
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

int	check_closed_sides(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (ft_isspace(str[i]) && str[i + 1] == '0')
			return (1);
		if (str[i] == '0' && ft_isspace(str[i + 1]))
			return (1);
		i++;
	}
	return (0);
}
