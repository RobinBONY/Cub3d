/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:18:17 by rbony             #+#    #+#             */
/*   Updated: 2021/11/10 12:21:43 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	strlen;
	char	*str;

	i = 0;
	strlen = 0;
	if (!s)
		return (NULL);
	if (start < ft_strlen(s))
	{
		strlen = ft_strlen(s + start);
		if (strlen > len)
			strlen = len;
	}
	str = malloc(strlen * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (i < strlen && s[i])
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
