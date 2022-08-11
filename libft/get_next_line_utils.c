/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:36:29 by rbony             #+#    #+#             */
/*   Updated: 2022/08/10 08:19:54 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gnl_ft_bzero(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		s[i++] = 0;
}

char	*gnl_ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if (c == '\0')
		return (&((char *)s)[i]);
	return (NULL);
}

char	*gnl_ft_memmove(char *dst, char *src)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return (dst);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst + i);
}

char	*gnl_ft_strncat(char *dest, char *src, int nb)
{
	int	i;
	int	next;

	i = 0;
	next = gnl_ft_strlen(dest);
	while (src[i] && i < nb)
	{
		dest[i + next] = src[i];
		i++;
	}
	dest[i + next] = '\0';
	return (dest);
}

char	*gnl_ft_strnjoin(char *s1, const char *s2, int n)
{
	char	*concat;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	concat = malloc((gnl_ft_strlen(s1) + n) * sizeof(char) + 1);
	if (!concat)
		return (NULL);
	concat[0] = '\0';
	gnl_ft_strncat(concat, (char *)s1, gnl_ft_strlen(s1));
	gnl_ft_strncat(concat, (char *)s2, n);
	if (s1)
		free(s1);
	return (concat);
}
