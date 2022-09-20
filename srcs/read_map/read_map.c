/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:08:31 by rbony             #+#    #+#             */
/*   Updated: 2022/09/07 12:33:03 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static t_list	*fill_map_list(char *mapname)
{
	int		fd;
	char	*buffer;
	t_list	*tmp;
	t_list	*head;

	head = NULL;
	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (!is_empty(buffer))
		{
			tmp = ft_lstnew(buffer);
			if (!tmp)
				return (ft_lstclear(&head));
			ft_lstadd_back(&head, tmp);
		}
		else
			free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (head);
}

int	parse_map(t_game *game, t_list *list)
{
	if (check_map_layout(list, game))
		return (1);
	return (create_int_map(game, list));
}

static int	parse_file(t_game *game, char *mapname)
{
	t_list	*head;
	t_list	*tmp;

	head = fill_map_list(mapname);
	if (!head)
		return (error_1(READING_FILE));
	tmp = head;
	if (parse_textures(game, &tmp))
		return (1);
	if (parse_map(game, tmp))
		return (error_1(INVALID_MAP));
	ft_lstclear(&head);
	print_data(game);
	return (0);
}

// reads the map and fill the game attributes
int	read_map(t_game *game, char *mapname)
{
	int	file_exists;

	file_exists = access(mapname, R_OK);
	if (check_ext(mapname, ".cub") && file_exists == 0)
		return (parse_file(game, mapname));
	if (file_exists == -1)
	{
		if (access(mapname, F_OK) == 0)
			return (error_1(PD));
		else
			return (error_1(FNF));
	}
	else
		return (error_1(INVALID_FORMAT));
	return (1);
}
