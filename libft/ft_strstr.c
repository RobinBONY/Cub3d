/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:37:30 by rbony             #+#    #+#             */
/*   Updated: 2022/08/11 11:53:49 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	needlelen;
	size_t	len;

	i = 0;
	needlelen = ft_strlen(needle);
	len = ft_strlen(haystack);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i + needlelen <= len)
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(haystack + i, needle, needlelen) == 0)
			{
				return ((char *)haystack + i);
			}
		}
		i++;
	}
	return (NULL);
}
