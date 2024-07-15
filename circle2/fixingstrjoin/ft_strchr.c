/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:25:11 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/11 16:28:18 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*temp;

	temp = (unsigned char *) s;
	while (*temp != '\0')
	{
		if (*temp == (unsigned char) c)
			return ((char *)temp);
		temp++;
	}
	if ((unsigned char) c == '\0')
		return ((char *)temp);
	return (NULL);
}
