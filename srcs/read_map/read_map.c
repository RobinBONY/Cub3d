/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:08:31 by rbony             #+#    #+#             */
/*   Updated: 2022/08/11 16:28:39 by alakhdar         ###   ########lyon.fr   */
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

/*char	*find_keyword(char *line)
{
	char						*keyword;

	keyword = ft_strstr(line, "NO ");
	if (keyword)
		return (keyword);
	keyword = ft_strstr(line, "SO ");
	if (keyword)
		return (keyword);
	keyword = ft_strstr(line, "EA ");
	if (keyword)
		return (keyword);
	keyword = ft_strstr(line, "WE ");
	if (keyword)
		return (keyword);
	keyword = ft_strstr(line, "F ");
	if (keyword)
		return (keyword);
	keyword = ft_strstr(line, "C ");
	if (keyword)
		return (keyword);
	return (NULL);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	check_and_assign(t_game *game, char **split, int splitsize)
{
	if (splitsize == 2)
	{
		
	}
	else if (splitsize == 1)
		return (texture_parsing_error(split[0]));
	else
		printf("%s %s\n", ERROR, INVALID_FORMAT);
	return (1);
}

static int	parse_textures(t_game *game, t_list **list)
{
	int		i;
	char	**split;

	i = 0;
	while (i < 6)
	{
		split = ft_split((*list)->content, ' ');
		if (!split)
		{
			printf("%s %s\n", ERROR, READING_FILE);
			return (1);
		}
		//check_and_assign(game, split, split_size(split));
		i++;
		free_split(split);
		*list = (*list)->next;
	}
	return (0);
}*/

int	parse_map(t_game *game, t_list *list)
{
	int	i;

	i = 0;
	if (!check_map_layout(list, game))
	{
		printf("%s %s\n", ERROR, INVALID_MAP);
		return (0);
	}
	return (create_int_map(game, list));
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
	//if (parse_textures(game, &tmp))
		//return (0);
	if (parse_map(game, tmp))
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
		printf("%s %s\n", ERROR, INVALID_FORMAT);
	print_int_tab(game->map);
	return (0);
}
