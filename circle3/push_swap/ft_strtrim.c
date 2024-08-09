/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/19 15:59:42 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_isset(char a, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	int		s1len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	s1len = ft_strlen(s1);
	while (ft_isset(s1[i], set) && s1[i] != '\0')
		i++;
	if (i == s1len)
		return (ft_strdup(""));
	while (ft_isset(s1[s1len - j - 1], set))
		j++;
	dst = (char *) malloc(s1len - i - j + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, &s1[i], s1len - i - j + 1);
	return (dst);
}
