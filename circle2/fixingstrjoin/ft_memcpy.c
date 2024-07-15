/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:25:11 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/11 16:28:40 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*tempsrc;
	char	*tempdest;

	tempsrc = (char *)src;
	tempdest = (char *)dest;
	while (n-- > 0)
	{
		if (!dest && !src)
			return (NULL);
		*tempdest = *tempsrc;
		tempdest++;
		tempsrc++;
	}
	return (dest);
}
