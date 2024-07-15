#include "push_swap.h"

void testing_median(t_stack *a)
{
	while (a)
	{
		printf("%d\n",a->above_median);
		a = a->next;
	}
	printf("\n");
}

void testing_target(t_stack *a)
{
	if (!a)
		printf ("NULL");
	else
	{
		while(a)
		{
			printf("Nodeint:%d\nTargetint:%d\n",a->num,a->target_node->num);
			a = a->next;
		}
	}
	printf("\n");
}

void testing_index(t_stack *a)
{
	while(a)
	{
		printf("Nodeindex:%d\nListlen:%d\n",a->index,a->max_index);
		a = a->next;
	}
	printf("\n");
}

void testing_push_cost(t_stack *a)
{
	while(a)
	{
		printf("Pushcost:%d\n",a->push_cost);
		a = a->next;
	}
	printf("\n");
}

void testing_cheapest(t_stack *a)
{
	while(a)
	{
		printf("cheapest:%d\n",a->cheapest);
		a = a->next;
	}
	printf("\n");
}

void show_full_node(t_stack *a)
{
    t_stack *current = a;

    if (!current)
    {
        printf("Stack is empty.\n");
        return;
    }
	    if (!(current->target_node))
    {
        printf("Target empty.\n");
        return;
    }

    printf("---------------------------------------------------------------------\n");
    printf("| %-5s | %-5s | %-9s | %-8s | %-6s | %-8s | %-10s | %-10s | %-10s |\n", 
           "Num", "Idx", "Max_Idx", "Cost", "Median", "Cheapest", "Target", "Next", "Prev");
    printf("---------------------------------------------------------------------\n");

    while (current)
    {
        printf("| %-5d | %-5d | %-9d | %-8d | %-6d | %-8d | %-10d | %-10p | %-10p |\n", 
               current->num, current->index, current->max_index, current->push_cost, 
               current->above_median, current->cheapest, 
               current->target_node->num, current->next, current->prev);
        current = current->next;
    }

    printf("---------------------------------------------------------------------\n");
}

void trouble(t_stack *a, t_stack *b)
{	
	update_node_info(a, b);
	show_full_node(a);
	show_full_node(b);
}