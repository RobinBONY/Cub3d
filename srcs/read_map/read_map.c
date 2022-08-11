/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:08:31 by rbony             #+#    #+#             */
/*   Updated: 2022/08/10 17:31:47 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	check_ext(char *str)
{
	char	*tmp;
	int		length;

	length = ft_strlen(str);
	if (length <= 4 || str[length - 5] == '/')
		return (0);
	if (ft_strncmp(str + length - 4, ".cub", 4))
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

static int	parse_map(t_game *game, char *mapname)
{
	
}

// reads the map and fill the game attributes
int	read_map(t_game *game, char *mapname)
{
	int	file_exists;

	file_exists = access(mapname, R_OK);
	if (game && check_ext(mapname) == 0 && file_exists == 0)
		return (parse_map(game, mapname));
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
