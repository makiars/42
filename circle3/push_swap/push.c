#include "push_swap.h"

void pa(t_stack **a,t_stack **b)
{
	t_stack *b_start;

	if (!b || !(*b))
		return;
	if ((*b)->next == NULL)
	{
		(*a)->prev = *b;
		(*b)->next = *a;
		(*b)->prev = NULL;
		*a = *b;
		*b = NULL;
	}
	else
	{
		b_start = (*a)->next;
		(*b)->next->prev = NULL;
		(*a)->prev = *b;
		(*b)->next = *a;
		*a = *b;
		*a = b_start;
	}
	update_node_info(*a, *b);
	write(1,"pa\n",3);
}

void pb(t_stack **a,t_stack **b)
{
	t_stack *a_start;

	if (!a || !(*a))
		return;
	if (!b || !(*b))
	{
		a_start = (*a)->next;
		(*a)->next->prev = NULL;
		(*a)->next = NULL;
		*b = *a;
		*a = a_start;
	}
	else
	{
		a_start = (*a)->next;
		(*a)->next->prev = NULL;
		(*b)->prev = *a;
		(*a)->next = *b;
		*b = *a;
		(*a)->prev = NULL;
		*a = a_start;
	}
	update_node_info(*a, *b);
	write(1,"pb\n",3);
}