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

void	calc_push_cost(t_stack *a)
{
	if (!a)
		return ;
	while (a)
	{
		if ((a->above_median && a->target_node->above_median)
			|| (a->above_median == 0 && a->target_node->above_median == 0))
		{
			a->push_cost = shared_cost(a);
		}
		else if (a->above_median == 1 && a->target_node->above_median == 0)
			a->push_cost = a->index + a->target_node->max_index
				- a->target_node->index + 1;
		else if (a->above_median == 0 && a->target_node->above_median == 1)
			a->push_cost = a->max_index - a->index + a->target_node->index + 1;
		a = a->next;
	}
}

void	update_node_info(t_stack *a, t_stack *b)
{
	add_median(a);
	add_median(b);
	find_target_node(a, b);
	find_target_node(b, a);
	update_index(a);
	update_index(b);
	calc_push_cost(a);
	calc_push_cost(b);
	calc_cheapest(a);
	calc_cheapest(b);
}
