#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_stack
{
	int				num;
	int				index;
	int				max_index;
	int				push_cost;
	int				above_median;
	int				cheapest;
	struct s_stack	*target_node;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

void	free_list(t_stack *head);
void	update_node_info(t_stack *a, t_stack *b);

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "nodeinfo.c"
# include "nodeinfo2.c"
# include "swap.c"
# include "rotate.c"
# include "reverse_rotate.c"
# include "push.c"
# include "helper.c"
# include "algorithm.c"

#endif