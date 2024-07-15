/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:28:29 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/11 14:19:57 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*temps1;
	unsigned char	*temps2;

	temps1 = (unsigned char *)s1;
	temps2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n-- > 0)
	{
		if (*temps1 != *temps2)
			return (*temps1 - *temps2);
		temps1++;
		temps2++;
	}
	return (0);
}
