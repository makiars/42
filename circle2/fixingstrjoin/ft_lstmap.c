/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:52:11 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/22 11:19:16 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*var;
	t_list	*newlst;
	t_list	*newelem;

	if (!lst || !f || !del)
		return (NULL);
	newlst = NULL;
	while (lst != NULL)
	{
		var = f(lst->content);
		newelem = ft_lstnew(var);
		if (newelem == NULL)
			return (ft_lstclear(&newlst, del), free(var), NULL);
		ft_lstadd_back(&newlst, newelem);
		lst = lst->next;
	}
	return (newlst);
}
