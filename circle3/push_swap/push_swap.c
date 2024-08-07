#include "push_swap.h"

t_stack *add_node(t_stack *lst)
{
	t_stack *start;
	t_stack *new_node;

	start = lst;
	if (!lst)
	{
		lst = malloc(sizeof(t_stack));
		if (!lst)
			return (NULL);
		lst->prev = NULL;
		lst->next = NULL;
		return (lst);
	}
	while ((lst->next))
		lst = lst->next;
	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->prev = lst;
	lst->next = new_node;
	return (start);
}

t_stack *insert_num(t_stack *a, int argc, char **argv)
{
	t_stack *start;
	int i;

	start = a;
	i = 1;
	while(i < argc && a != NULL)
	{
		a->num = atoi(argv[i]);//TODO: exchange atoi for ft_atoi
		i++;
		a = a->next;
	}
	return(start);
}

void b_max_on_top(t_stack **a, t_stack **b)
{
	t_stack *b_max;
	t_stack *b_start;

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

t_stack *last_node(t_stack *a)
{
	while(a->next != NULL)
		a = a->next;
	return (a);
}

t_stack *max_num(t_stack *a)
{
	t_stack *a_max;

	a_max = a;
	while(a != NULL)
	{
		if (a_max->num < a->num)
			a_max = a;
		a = a->next;
	}
	return (a_max);
}

t_stack *min_num(t_stack *a)
{
	t_stack *a_min;

	a_min = a;
	while(a != NULL)
	{
		if (a_min->num > a->num)
			a_min = a;
		a = a->next;
	}
	return (a_min);
}


void push_to_a(t_stack **a, t_stack **b)
{
	t_stack *a_last;
	t_stack *a_min;


	while ((*b) && max_num(*b)->num > min_num(*a)->num)
	{
		while (last_node(*a)->num > (*b)->num)
			rra(a);
		if ((*b)->num > last_node(*a)->num)
			pa(a, b);
	}
	while (*a != min_num(*a))
		rra(a);
	while((*b)!= NULL)
		pa(a, b);
}


void sort_3(t_stack **a)
{
	if ((*a)->num < (*a)->next->num && (*a)->next->num < (*a)->next->next->num)
		return;
	else if ((*a)->num < (*a)->next->num && (*a)->next->num > (*a)->next->next->num)
		rra(a);
	else if ((*a)->num > (*a)->next->num && (*a)->next->num < (*a)->next->next->num)
		ra(a);
	else if ((*a)->num > (*a)->next->num && (*a)->next->num > (*a)->next->next->num)
	{
		sa(a);
		rra(a);
	}
	else if ((*a)->num < (*a)->next->num && (*a)->next->num > (*a)->next->next->num)
	{
		sa(a);
		ra(a);
	}
	else if ((*a)->num > (*a)->next->num && (*a)->next->num < (*a)->next->next->num)
		sa(a);
}


void push_to_b(t_stack **a, t_stack **b)
{
    t_stack *current_a;

    if (*b == NULL || !b)
		pb(a, b);
	while ((*a)->max_index != 2)
    {
        current_a = *a;
		while (current_a->cheapest != 1 && current_a != NULL)
			current_a = current_a->next;
		if (current_a->index == 0 && current_a->target_node->index == 0)
			pb(a, b);
		else if (current_a->above_median == 1 && current_a->target_node->above_median == 1 && current_a->index != 0 && current_a->target_node->index != 0)
			rr(a, b);
		else if (current_a->above_median == 0 && current_a->target_node->above_median == 0 && current_a->index != 0 && current_a->target_node->index != 0)
			rrr(a, b);
		else if (current_a->above_median == 1 && current_a->index != 0)
        	ra(a);
		else if (current_a->above_median == 0 && current_a->index != 0)
        	rra(a);
		else if (current_a->target_node->above_median == 1 && current_a->target_node->index != 0)
        	rb(b);
		else if (current_a->target_node->above_median == 0 && current_a->target_node->index != 0)
        	rrb(b);
		update_node_info(*a, *b);
	}
}


int main (int argc, char **argv)
{
	t_stack *a;
	t_stack *b;
	int i;

	if (argc == 1)
		return (0);
	i = 0;
	a = NULL;
	b = NULL;
	while (++i < argc)
		a = add_node(a);
	a = insert_num(a,argc,argv);

	push_to_b(&a, &b);
	sort_3(&a);
	update_node_info(a, b);
	b_max_on_top(&a, &b);
	push_to_a(&a, &b);
}
