/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:18:57 by rbony             #+#    #+#             */
/*   Updated: 2021/11/12 10:06:58 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_int_size(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n >= 10)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*ft_toascii(char *str, int n, size_t size)
{
	if (n >= 10)
	{
		str[size--] = n % 10 + '0';
		ft_toascii(str, n / 10, size);
	}
	else
		str[size--] = n + '0';
	return (str);
}

static char	*ft_intmintoa(void)
{
	char	*a;

	a = malloc(11 * sizeof(char) + 1);
	ft_strlcpy(a, "-2147483648", 12);
	return (a);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	size;

	if (n == -2147483648)
		return (ft_intmintoa());
	size = ft_int_size(n);
	str = malloc(size * sizeof(char) + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	str[size--] = '\0';
	return (ft_toascii(str, n, size));
}
