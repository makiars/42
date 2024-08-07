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

t_stack	*add_node(t_stack *lst)
{
	t_stack	*start;
	t_stack	*new_node;

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
		return (free_list(start), NULL);
	new_node->next = NULL;
	new_node->prev = lst;
	lst->next = new_node;
	return (start);
}

t_stack	*insert_num(t_stack *a, int argc, char **argv)
{
	t_stack	*start;
	int		i;

	start = a;
	i = 1;
	while (i < argc && a != NULL)
	{
		a->num = atoi(argv[i]);//TODO: exchange atoi for ft_atoi
		i++;
		a = a->next;
	}
	return (start);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		i;

	if (argc == 1)
		return (0);
	i = 0;
	a = NULL;
	b = NULL;
	while (++i < argc)
		a = add_node(a);
	a = insert_num(a, argc, argv);
	if (argc < 4) //more input error handling needed, use ito and atoi
		write(2, "Error\n", 6);
	else if (argc == 3)
		sort_3(&a);
	else
	{
		push_to_b(&a, &b);
		sort_3(&a);
		update_node_info(a, b);
		b_max_on_top(&a, &b);
		push_to_a(&a, &b);
	}
	free_list(a);
	free_list(b);
}
