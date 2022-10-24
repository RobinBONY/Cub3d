/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:36:27 by rbony             #+#    #+#             */
/*   Updated: 2022/08/13 14:42:38 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_get_line(char *line, char *buffer, int n, char *separator)
{
	char	*result;

	result = gnl_ft_strnjoin(line, buffer, n);
	if (separator)
		gnl_ft_bzero(gnl_ft_memmove(buffer, separator + 1));
	else
		gnl_ft_bzero(buffer);
	return (result);
}

char	*ft_get_leftover(char *buffer)
{
	char	*result;
	char	*separator;

	separator = gnl_ft_strchr(buffer, '\n');
	if (separator)
		result = gnl_ft_strnjoin(NULL, buffer, separator - buffer + 1);
	else
		result = gnl_ft_strnjoin(NULL, buffer, gnl_ft_strlen(buffer));
	if (separator)
		gnl_ft_bzero(gnl_ft_memmove(buffer, separator + 1));
	else
		gnl_ft_bzero(buffer);
	return (result);
}

char	*ft_make_line(char *line, char *buffer, int fd)
{
	char		*separator;

	while (!gnl_ft_strchr(line, '\n') && read(fd, buffer, BUFFER_SIZE))
	{
		separator = gnl_ft_strchr(buffer, '\n');
		if (buffer[0] == '\0')
		{
			free(line);
			return (NULL);
		}
		if (separator)
			line = ft_get_line(line, buffer, separator - buffer + 1, separator);
		else if (gnl_ft_strlen(buffer) < BUFFER_SIZE)
			line = ft_get_line(line, buffer, gnl_ft_strlen(buffer), NULL);
		else
			line = ft_get_line(line, buffer, BUFFER_SIZE, NULL);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*tmp;

	tmp = NULL;
	buffer[BUFFER_SIZE] = '\0';
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = ft_get_leftover(buffer);
	if (!line)
		return (NULL);
	line = ft_make_line(line, buffer, fd);
	if (line && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	tmp = ft_strchr(line, '\n');
	if (tmp)
		tmp[ft_strlen(tmp) - 1] = '\0';
	return (line);
}
