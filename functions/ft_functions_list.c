/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:15:00 by lmellos           #+#    #+#             */
/*   Updated: 2021/03/30 16:17:37 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*element;

	element = ft_malloc(sizeof(t_list), NULL);
	element->content = content;
	element->next = NULL;
	return (element);
}

t_type	*ft_lstnew_for_obj(void *content, int id)
{
	t_type	*element;

	element = ft_malloc(sizeof(t_type), NULL);
	element->content = content;
	element->id = id;
	element->next = NULL;
	return (element);
}

void	ft_lstadd_back_for_obj(t_type **lst, t_type *new)
{
	t_type	*begin;

	begin = *lst;
	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new;
	}
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*begin;

	begin = *lst;
	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}
