/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:03:00 by rbony             #+#    #+#             */
/*   Updated: 2022/08/11 10:56:37 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*last;

	if (!*lst)
		return ;
	while (*lst)
	{
		last = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = last;
	}
	lst = NULL;
}
