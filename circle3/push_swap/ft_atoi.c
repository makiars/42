/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:25:11 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/22 13:27:51 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi(const char *nptr)
{
	int				minus;
	unsigned long	num;
	long			n;

	n = 0;
	num = 0;
	minus = 1;
	while ((*nptr >= 9 && *nptr <= 13) || (*nptr == ' '))
		nptr++;
	if (*nptr == '-')
		minus = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = (n + *nptr - '0') * 10;
		num = (num + *nptr - '0') * 10;
		if ((num != (unsigned long)n) && (minus == -1))
			return (0);
		else if ((num != (unsigned long)n) && (minus == 1))
			return (-1);
		nptr++;
	}
	n /= 10;
	return ((int)(n * minus));
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