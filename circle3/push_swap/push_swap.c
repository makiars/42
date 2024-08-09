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

int	checkdup(t_stack *a, t_stack *a_start)
{
	while (a_start != a)
	{
		if (a_start->num == a->num)
			return (0);
		a_start = a_start->next;
	}
	return (1);
}

t_stack	*insert_num(t_stack *a, int argc, char **argv)
{
	int		check;
	t_stack	*start;
	int		i;

	start = a;
	i = 1;
	check = -1;
	while (i < argc && a != NULL)
	{
		a->num = ft_atoi(argv[i]);
		if (ft_strcmp(ft_itoa(a->num), argv[i]))
			return (NULL);
		check = checkdup(a, start);
		if (!check)
			return (NULL);
		i++;
		a = a->next;
	}
	return (start);
}

int	is_sorted(t_stack *a)
{
	int	prev;

	if (!a)
		return (0);
	prev = a->num;
	a = a->next;
	while (a)
	{
		if (a->num < prev)
			return (0);
		prev = a->num;
		a = a->next;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		i;

	if (argc < 4)
		return (0);
	i = 0;
	a = NULL;
	b = NULL;
	while (++i < argc)
		a = add_node(a);
	a = insert_num(a, argc, argv);
	if (is_sorted(a))
		return (0);
	if (!a)
		write(2, "Error\n", 6);
	else if (argc == 4)
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
