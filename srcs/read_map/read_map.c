/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:08:31 by rbony             #+#    #+#             */
/*   Updated: 2022/08/11 12:30:48 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

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
		tmp = ft_lstnew(buffer);
		if (!tmp)
		{
			ft_lstclear(&head);
			return (NULL);
		}
		ft_lstadd_back(&head, tmp);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (head);
}

static int	parse_textures(t_game *game, t_list **list)
{
	
}

static int	parse_map(t_game *game, t_list **list)
{
	
}

static int	parse_file(t_game *game, char *mapname)
{
	t_list	*head;
	t_list	*tmp;

	head = fill_map_list(mapname);
	if (!head)
	{
		printf("%s %s\n", ERROR, READING_FILE);
		return (0);
	}
	tmp = head;
	if (parse_textures(game, &tmp))
	{
		printf("%s %s\n", ERROR, MISS_N_TEXTURE);
		return (0);
	}
	if (parse_map(game, &tmp))
	{
		printf("%s %s\n", ERROR, INVALID_MAP);
		return (0);
	}
	ft_lstclear(&head);
	return (1);
}

// reads the map and fill the game attributes
int	read_map(t_game *game, char *mapname)
{
	int	file_exists;

	file_exists = access(mapname, R_OK);
	if (game && check_ext(mapname) && file_exists == 0)
		return (parse_file(game, mapname));
	if (file_exists == -1)
	{
		if (access(mapname, F_OK) == 0)
			printf("%s %s\n", ERROR, PD);
		else
			printf("%s %s\n", ERROR, FNF);
	}
	else
		printf("%s %s\n", ERROR, INVALID_EXT);
	return (0);
}
