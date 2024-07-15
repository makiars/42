/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:25:11 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/11 13:52:59 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*temp;

	temp = (unsigned char *) s;
	while (*temp != '\0')
		temp++;
	if ((unsigned char) c == '\0')
		return ((char *)temp);
	while (*temp != (unsigned char) c)
	{
		if ((unsigned char *) s == temp)
			return (NULL);
		temp--;
	}
	return ((char *)temp);
}
