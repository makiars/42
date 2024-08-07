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

t_stack	*last_node(t_stack *a)
{
	while (a->next != NULL)
		a = a->next;
	return (a);
}

t_stack	*max_num(t_stack *a)
{
	t_stack	*a_max;

	a_max = a;
	while (a != NULL)
	{
		if (a_max->num < a->num)
			a_max = a;
		a = a->next;
	}
	return (a_max);
}

t_stack	*min_num(t_stack *a)
{
	t_stack	*a_min;

	a_min = a;
	while (a != NULL)
	{
		if (a_min->num > a->num)
			a_min = a;
		a = a->next;
	}
	return (a_min);
}

void	free_list(t_stack *head)
{
	t_stack	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}
