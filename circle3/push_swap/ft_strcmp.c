/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:28:29 by marsenij          #+#    #+#             */
/*   Updated: 2024/02/20 09:57:16 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_strcmp(char *s1, char *s2)
{
	int		a;

	if (!s1 || !s2)
		return (0);
	a = 0;
	while ((*s1 != '\0') || (*s2 != '\0'))
	{
		if (*s1 < *s2)
		{
			a = *s1 - *s2;
			return (a);
		}
		else if (*s1 > *s2)
		{
			a = *s1 - *s2;
			return (a);
		}
		s1++;
		s2++;
	}
	return (a);
}

t_stack	*create_all_nodes(t_stack *a, int argc, int issplit)
{
	int	i;

	i = 0;
	if (issplit)
		i = -1;
	while (++i < argc)
	{
		a = add_node(a);
		if (!a)
			return (free_list(a), NULL);
	}
	return (a);
}
