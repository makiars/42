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
		a->num = atoi(argv[i]);//exchange atoi for ft_atoi
		i++;
		a = a->next;
	}
	return(start);
}

void rotate2top(t_stack **a, t_stack **b)
{
    while (*a && (*a)->index != 0 && *b && (*b)->index != 0) 
	{
        rr(a, b);
        update_node_info(*a, *b);
    }
    while (*a && (*a)->index != 0) 
	{
        ra(a);
        update_node_info(*a, *b);
		show_full_node(*a);
		show_full_node(*b);
    }
    while (*b && (*b)->index != 0) 
	{
        rb(b);
        update_node_info(*a, *b);
    }
}

void rotate2bottom(t_stack **a, t_stack **b)
{
    while (*a && (*a)->index != 0 && *b && (*b)->index != 0) {
        rrr (a, b);
        update_node_info(*a, *b);
    }
    while (*a && (*a)->index != 0) {
        rra(a);
        update_node_info(*a, *b);
    }
    while (*b && (*b)->index != 0) {
        rrb(b);
        update_node_info(*a, *b);
    }
}

void push_to_b(t_stack **a, t_stack **b)
{
    t_stack *current_a;

    if (*b == NULL)
        pb(a, b);
   
    while ((*a)->max_index != 2)
    {
        current_a = *a;
        while (current_a->cheapest != 1 && current_a != NULL)
            current_a = current_a->next;
		if (current_a->index == 0 && current_a->target_node->index == 0)
        {
			trouble(*a, *b);
			pb(a, b);
    		update_node_info(*a, *b);
		}
        else if (current_a->above_median == 1 && current_a->target_node->above_median == 1 && current_a->index != 0 && current_a->target_node->index != 0)
        {
            trouble(*a, *b);
            rr(a, b);
			update_node_info(*a, *b);
        }
        else if (current_a->above_median == 0 && current_a->target_node->above_median == 0 && current_a->index != 0 && current_a->target_node->index != 0)
        {
            trouble(*a, *b);
            rrr(a, b);
			update_node_info(*a, *b);
        }
        else if (current_a->above_median == 1 && current_a->index != 0)
        {
            trouble(*a, *b);
            ra(a);
			update_node_info(*a, *b);
        }
        else if (current_a->above_median == 0 && current_a->index != 0)
        {
            trouble(*a, *b);
            rra(a);
			update_node_info(*a, *b);
        }
        else if (current_a->target_node->above_median == 1 && current_a->target_node->index != 0)
        {
            trouble(*a, *b);
            rb(b);
			update_node_info(*a, *b);
        }
        else if (current_a->target_node->above_median == 0 && current_a->target_node->index != 0)
        {
            trouble(*a, *b);
            rrb(b);
			update_node_info(*a, *b);
        }
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
	
	pb(&a,&b);
	update_node_info(a, b);
	/*sa(&a);
	update_node_info(a, b);
	show_full_node(a);
	show_full_node(b);
	ra(&a);
	update_node_info(a, b);
	show_full_node(a);
	show_full_node(b);
	rra(&a);
	update_node_info(a, b);
	show_full_node(a);
	show_full_node(b);
	pb(&a,&b);
	update_node_info(a, b);
	show_full_node(a);
	show_full_node(b);*/
	push_to_b(&a, &b);
	update_node_info(a, b);
	show_full_node(a);
	show_full_node(b);
	/*push_to_b(&a, &b);
	update_node_info(a, b);
	show_full_node(a);
	show_full_node(b);*/
}

