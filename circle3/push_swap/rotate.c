#include "push_swap.h"

void rotate(t_stack **a)
{
	t_stack *first;
	t_stack *second;
	t_stack *last;

	if (*a == NULL || (*a)->next == NULL)
		return ;
	first = *a;
	second = first->next;
	second->prev = NULL;
	while ((*a)->next)
		*a = (*a)->next;
	last = *a;
	last->next = first;
	first->next = NULL;
	first->prev = last;
	*a = second;
	
}

void ra (t_stack **a)
{
    rotate(a);
    write(1,"ra\n",3);
}

void rb (t_stack **b)
{
    rotate(b);
    write(1,"rb\n",3);
}

void rr (t_stack **a, t_stack **b)
{
    rotate(a);
    rotate(b);
    write(1,"rr\n",3);
}