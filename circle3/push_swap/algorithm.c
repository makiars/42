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

void	b_max_on_top(t_stack **a, t_stack **b)
{
	t_stack	*b_max;
	t_stack	*b_start;

	b_start = *b;
	b_max = *b;
	while ((*b) != NULL)
	{
		if ((*b)->num > b_max->num)
			b_max = *b;
		*b = (*b)->next;
	}
	*b = b_start;
	while (b_max->index != 0)
	{
		if (b_max->above_median)
			rb(b);
		if (!(b_max->above_median))
			rrb(b);
		update_node_info(*a, *b);
	}
}

void	push_to_a(t_stack **a, t_stack **b)
{
	while ((*b) && max_num(*b)->num > min_num(*a)->num)
	{
		while (last_node(*a)->num > (*b)->num)
			rra(a);
		if ((*b)->num > last_node(*a)->num)
			pa(a, b);
	}
	while (*a != min_num(*a))
		rra(a);
	while ((*b) != NULL)
		pa(a, b);
}

void	sort_3(t_stack **a)
{
	if ((*a)->num < (*a)->next->num && (*a)->next->num < (*a)->next->next->num)
		return ;
	else if ((*a)->num < (*a)->next->num
		&& (*a)->next->num > (*a)->next->next->num)
		rra(a);
	else if ((*a)->num > (*a)->next->num
		&& (*a)->next->num < (*a)->next->next->num)
		ra(a);
	else if ((*a)->num > (*a)->next->num
		&& (*a)->next->num > (*a)->next->next->num)
	{
		sa(a);
		rra(a);
	}
	else if ((*a)->num < (*a)->next->num
		&& (*a)->next->num > (*a)->next->next->num)
	{
		sa(a);
		ra(a);
	}
	else if ((*a)->num > (*a)->next->num
		&& (*a)->next->num < (*a)->next->next->num)
		sa(a);
}

void	push_to_b_logic(t_stack **a, t_stack *curr_a, t_stack **b)
{
	if (curr_a->index == 0 && curr_a->target_node->index == 0)
		pb(a, b);
	else if (curr_a->above_median == 1 && curr_a->target_node->above_median
		== 1 && curr_a->index != 0 && curr_a->target_node->index != 0)
		rr(a, b);
	else if (curr_a->above_median == 0 && curr_a->target_node->above_median
		== 0 && curr_a->index != 0 && curr_a->target_node->index != 0)
		rrr(a, b);
	else if (curr_a->above_median == 1 && curr_a->index != 0)
		ra(a);
	else if (curr_a->above_median == 0 && curr_a->index != 0)
		rra(a);
	else if (curr_a->target_node->above_median
		== 1 && curr_a->target_node->index != 0)
		rb(b);
	else if (curr_a->target_node->above_median
		== 0 && curr_a->target_node->index != 0)
		rrb(b);
}

void	push_to_b(t_stack **a, t_stack **b)
{
	t_stack	*current_a;

	if (*b == NULL || !b)
		pb(a, b);
	while ((*a)->max_index != 2)
	{
		current_a = *a;
		while (current_a->cheapest != 1 && current_a != NULL)
			current_a = current_a->next;
		push_to_b_logic(a, current_a, b);
		update_node_info(*a, *b);
	}
}
