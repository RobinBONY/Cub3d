/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:52:28 by alakhdar          #+#    #+#             */
/*   Updated: 2022/08/11 12:18:58 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	check_ext(char *str)
{
	char	*tmp;

	tmp = ft_strstr(str, ".cub");
	if (!tmp)
		return (0);
	if (ft_strcmp(tmp, ".cub"))
		return (0);
	return (1);
}
