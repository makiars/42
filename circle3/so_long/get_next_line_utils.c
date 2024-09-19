/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:36:46 by aruckenb          #+#    #+#             */
/*   Updated: 2024/04/29 10:30:33 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

char	*ft_strchr(const char *str, int c)
{
	char	*temp;
	char	letter;
	int		len;
	int		count;

	if (str == NULL)
		return (NULL);
	count = 0;
	len = 0;
	temp = (char *)str;
	letter = (char)c;
	len = ft_strlen(temp);
	while (count <= len)
	{
		if (temp[count] == letter)
			return (&temp[count]);
		count++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		count;
	char	*new_string;

	len = 1;
	count = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s2);
	new_string = malloc(len * sizeof(char));
	if (new_string == NULL)
		return (0);
	len = 0;
	while (s1 && s1[len])
		new_string[count++] = s1[len++];
	len = 0;
	while (s2 && s2[len])
		new_string[count++] = s2[len++];
	new_string[count] = '\0';
	return (new_string);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	char	*start;

	start = dest;
	while (*src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = *src;
	return (start);
}

char	*ft_strdup(const char *src)
{
	char	*characterstring;
	char	*temp;
	int		len;

	if (!src)
		return (0);
	len = ft_strlen(src);
	len++;
	characterstring = (char *)malloc(len);
	if (characterstring == NULL)
		return (0);
	temp = ft_strcpy(characterstring, src);
	if (!temp)
		return (0);
	return (temp);
}
