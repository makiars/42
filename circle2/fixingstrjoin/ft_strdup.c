/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:35:08 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/15 12:44:15 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		srclen;
	char	*dest;
	int		i;

	srclen = ft_strlen(src);
	dest = (char *)malloc(srclen + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (srclen > 0)
	{
		dest[i] = src[i];
		i++;
		srclen--;
	}
	dest[i] = '\0';
	return (dest);
}
