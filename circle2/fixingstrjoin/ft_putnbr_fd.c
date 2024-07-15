/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:10:56 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/22 11:28:04 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		array[i] = temp;
		j++;
		i--;
	}
}

static char	*ft_itoaput(int n, char *array)
{
	int		i;
	long	num;

	num = n;
	i = 0;
	if (num == 0)
		return ("0");
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
	return (&array[0]);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	int		i;
	char	*res;
	char	array[100];

	res = ft_itoaput(n, &array[0]);
	i = 0;
	len = ft_strlen(res);
	while (i < len)
	{
		write(fd, &res[i], 1);
		i++;
	}
}
