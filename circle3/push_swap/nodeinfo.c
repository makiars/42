#include "push_swap.h"

void add_median(t_stack *a)
{
	int cnt;
	int i;
	t_stack *start;

	i = 0;
	cnt = 0;
	start = a;
	if (!a)
		return ;
	while (a)
	{
		a->above_median = 0;
		cnt++;
		a = a->next;
	}
	a = start;
	cnt = cnt / 2 + (cnt % 2);
	while (i < cnt && a)
	{
		a->above_median = 1;
		i++;
		a = a->next;
	}
}

void find_target_node(t_stack *a, t_stack *b)
{
    t_stack *btemp;
    t_stack *b_start;

	if (!a || !b)
		return;
    while (a)
    {
        btemp = NULL;
        b_start = b;
        while (b_start)
        {
            if (b_start->num < a->num)
            {
                if (!btemp || b_start->num > btemp->num)
            		btemp = b_start;
            }
            b_start = b_start->next;
        }
        if (!btemp)
        	btemp = b;
        a->target_node = btemp;
        a = a->next;
    }
}

void update_index(t_stack *a)
{
	int i;

	i = 0;
	if (!a)
		return ;
	while(a->next)
	{
		a->index = i;
		i++;
		a = a->next;
	}
	a->index = i;
	while(a)
	{
		a->max_index = i;
		a = a->prev;
	}
}

void calc_cheapest(t_stack *a)
{
	t_stack *cheapest;
	t_stack *start;

	start = a;
	if (!a)
		return ;
	while (a)
	{
		a->cheapest = 0;
		a = a->next;
	}
	a = start;
	cheapest = a;
	while(a)
	{
		if (a->push_cost < cheapest->push_cost)
			cheapest = a;
		a = a->next;
	}
	cheapest->cheapest = 1;
}



void calc_push_cost(t_stack *a)
{
	if (!a)
		return ;
	while (a)
	{
		if (a->above_median)
			a->push_cost = a->index + a->target_node->index;
		else
			a->push_cost = a->max_index - a->index + 1;
		a = a->next;
	}
}



void update_node_info(t_stack *a, t_stack *b)
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
