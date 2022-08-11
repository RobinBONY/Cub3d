/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:28:13 by rbony             #+#    #+#             */
/*   Updated: 2021/11/10 13:52:03 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncat(char *dest, char *src, size_t nb)
{
	size_t	i;
	size_t	next;

	i = 0;
	next = ft_strlen(dest);
	while (src[i] && i < nb)
	{
		dest[i + next] = src[i];
		i++;
	}
	dest[i + next] = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	maxlen;
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	maxlen = 0;
	if (dstsize > dstlen)
		maxlen = dstsize - dstlen - 1;
	ft_strncat(dst, (char *)src, maxlen);
	if (dstsize < dstlen)
		return (dstsize + srclen);
	return (dstlen + srclen);
}
