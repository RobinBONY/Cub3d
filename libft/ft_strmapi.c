/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:19:13 by rbony             #+#    #+#             */
/*   Updated: 2021/11/10 14:43:33 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*cpy;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	cpy = ft_strdup(s);
	if (!cpy)
		return (NULL);
	while (i < len)
	{
		cpy[i] = (*f)(i, cpy[i]);
		i++;
	}
	return (cpy);
}
