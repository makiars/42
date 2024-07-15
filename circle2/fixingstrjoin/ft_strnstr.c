/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:25:11 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/22 11:40:36 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*haystack;
	char	*needle;

	if (big == NULL && little != NULL && len == 0)
		return (NULL);
	haystack = (char *) big;
	needle = (char *) little;
	i = 0;
	if (*needle == '\0')
		return ((char *) haystack);
	while (*haystack != '\0' && len > 0)
	{
		while (haystack[i] == needle[i] && len - i > 0 && haystack[i])
		{
			i++;
		}
		if (needle[i] == '\0')
			return ((char *) haystack);
		i = 0;
		haystack++;
		len--;
	}
	return (NULL);
}
