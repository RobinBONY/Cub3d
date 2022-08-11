/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:40:54 by rbony             #+#    #+#             */
/*   Updated: 2021/11/12 15:33:21 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_abortlst(t_list *newlst, void (*del)(void *))
{
	ft_lstclear(&newlst, del);
	return (NULL);
}

static t_list	*ft_first_node(t_list *lst, void *(*f)(void *))
{
	t_list	*newnode;
	void	*newcontent;

	newcontent = f(lst->content);
	if (!newcontent)
		return (NULL);
	newnode = ft_lstnew(newcontent);
	if (!newnode)
	{
		free(newcontent);
		return (NULL);
	}
	return (newnode);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newnode;
	void	*newcontent;

	if (!lst)
		return (NULL);
	newlst = ft_first_node(lst, f);
	if (!newlst)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		newcontent = f(lst->content);
		if (!newcontent)
			return (ft_abortlst(newlst, del));
		newnode = ft_lstnew(newcontent);
		if (!newnode)
			return (ft_abortlst(newlst, del));
		ft_lstadd_back(&newlst, newnode);
		lst = lst->next;
	}
	return (newlst);
}
