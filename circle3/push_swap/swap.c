#include "push_swap.h"

void swap(t_stack **a)
{
	t_stack *first;
	t_stack *second;

	if((*a) == NULL || (*a)->next == NULL)
		return ;
	first = *a;
	second = (*a)->next;
	first->next = second->next;
	if (second->next)
		first->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	*a = second;
}

void sa (t_stack **a)
{
    swap(a);
    write(1,"sa\n",3);
}

void sb (t_stack **b)
{
    swap(b);
    write(1,"sb\n",3);
}

void ss (t_stack **a, t_stack **b)
{
    swap(a);
    swap(b);
    write(1,"ss\n",3);
}