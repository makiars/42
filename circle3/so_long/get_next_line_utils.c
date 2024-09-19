/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:19:12 by marsenij          #+#    #+#             */
/*   Updated: 2024/05/30 11:50:03 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*temp;

	temp = (unsigned char *) s;
	if (!temp)
		return (NULL);
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;

	i = -1;
	j = -1;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	temp = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!temp)
		return (NULL);
	while (++i < s1len)
		temp[i] = s1[i];
	while (++j < s2len)
		temp[i + j] = s2[j];
	temp[i + j] = '\0';
	return (freeme(&s1), temp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (malloc(1));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;
	char	*str;

	if (!s)
		return (0);
	str = (char *)s;
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *src)
{
	int		srclen;
	char	*dest;
	int		i;

	if (!src)
		return (NULL);
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
