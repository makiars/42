/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:35:08 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/22 11:26:15 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*dest;
	size_t			i;

	i = 0;
	if (size != 0 && nmemb != (nmemb * size) / size)
		return (NULL);
	dest = (unsigned char *)malloc(size * nmemb * sizeof (unsigned char));
	if (dest == NULL)
		return (NULL);
	while (i < (size * nmemb))
	{
		dest[i] = '\0';
		i++;
	}
	return ((void *)dest);
}
