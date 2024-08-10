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
	char	*temp;

	start = a;
	i = 1;
	while (i < argc && a != NULL)
	{
		a->num = ft_atoi(argv[i]);
		temp = ft_itoa(a->num);
		if (!temp)
			return (free_list(start), NULL);
		if (ft_strcmp(temp, argv[i]))
			return (free(temp), free_list(start), NULL);
		if (checkdup(a, start))
			return (free(temp), free_list(start), write(2, "Error\n", 6), NULL);
		i++;
		a = a->next;
		free(temp);
	}
	return (start);
}

t_stack	*sortlogic(t_stack *a, t_stack*b, int argc)
{
	if (!a)
		write(2, "Error\n", 6);
	else if (argc == 4)
		sort_3(&a);
	else
	{
		push_to_b(&a, &b);
		update_node_info(a, b);
		sort_3(&a);
		update_node_info(a, b);
		b_max_on_top(&a, &b);
		update_node_info(a, b);
		push_to_a(&a, &b);
	}
	return (a);
}

int	init_split(char **split_a, char **argv)
{

	split_a = ft_split(argv[1], ' ');
	if (!split_a)
		return (0);
	if (wordcnt(split_a) > 1)
		return (1);
	else
		return (free_double_array(split_a), 0);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		i;
	char	**split_a;
	int		issplit;

	i = 0;
	a = NULL;
	b = NULL;
	split_a = ft_split(argv[1], ' ');
	if (!split_a)
		return (0);
	if (wordcnt(split_a) > 1) // put this into seperate function and add argc +1 and argv[0]
	{
		argc = wordcnt(split_a);
		argv = split_a;
		issplit = 1;
	}
	else if (argc < 4)
		return (free_double_array(split_a), 0);
	while (++i < argc)
	{
		a = add_node(a);
		if (!a)
			return (free_double_array(split_a), free_list(a), free_list(b), 0);
	}
	a = insert_num(a, argc, argv);
	free_double_array(split_a);
	if (!a)
		return (free_list(a), free_list(b), 0);
	if (is_sorted(a))
		return (free_list(a), free_list(b), 0);
	a = sortlogic(a, b, argc);
	free_list(a);
	free_list(b);
}
