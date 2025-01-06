/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/22 11:27:08 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_revarray(char *array, int i)
{
	char	temp;
	int		j;
	int		len;

	len = i;
	if (*array == '-')
		j = 1;
	else
		j = 0;
	while (j < len / 2 + 1)
	{
		temp = array[j];
		array[j] = array[i];
		array [i] = temp;
		j++;
		i--;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	len;
	char	*str;

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

void	calc_itoa(int num, char *array)
{
	int		i;

	i = 0;
	if (num < 0)
	{
		num = -num;
		array[0] = '-';
		i++;
	}
	while (num != 0)
	{
		array[i] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	array[i] = '\0';
	ft_revarray(array, i - 1);
}

char	*ft_itoa(int n)
{
	char	array[20];
	long	num;
	char	*dup;

	num = n;
	if (num == -2147483648)
		return (ft_strdup("-2147483648"));
	if (num == 0)
	{
		dup = ft_strdup("0");
		if (!dup)
			return (NULL);
		return (dup);
	}
	calc_itoa(num, array);
	dup = ft_strdup(&array[0]);
	if (!dup)
		return (NULL);
	return (dup);
}

