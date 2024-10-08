/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/22 11:27:08 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_stack **a)
{
	t_stack	*first;
	t_stack	*last;

	if (*a == NULL || (*a)->next == NULL)
		return ;
	first = *a;
	while ((*a)->next)
		*a = (*a)->next;
	last = *a;
	last->prev->next = NULL;
	last->next = first;
	first->prev = last;
	last->prev = NULL;
	*a = last;
}

void	rra(t_stack **a)
{
	reverse_rotate(a);
	write (1, "rra\n", 4);
}

void	rrb(t_stack **b)
{
	reverse_rotate(b);
	write (1, "rrb\n", 4);
}

void	rrr(t_stack **a, t_stack **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	write (1, "rrr\n", 4);
}
