/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:08:31 by rbony             #+#    #+#             */
/*   Updated: 2022/08/11 12:04:14 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	check_ext(char *str)
{
	char	*tmp;

	tmp = ft_strstr(str, ".cub");
	if (!tmp)
		return (0);
	if (ft_strcmp(tmp, ".cub"))
		return (0);
	return (1);
}

/*static int	get_height(char *file)
{
	int		fd;
	char	*line;
	int		height;

	height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close (fd);
	return (height);
}*/

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

static int	parse_map(/*t_game *game, */char *mapname)
{
	t_list	*head;
	t_list	*tmp;

	head = fill_map_list(mapname);
	tmp = head;
	while (tmp)
	{
		printf("%s", tmp->content);
		tmp = tmp->next;
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
		return (parse_map(/*game, */mapname));
	if (file_exists == -1)
	{
		if (access(mapname, F_OK) == 0)
			printf(PD);
		else
			printf(FNF);
	}
	else
		printf(INVALID_EXT);
	return (0);
}
