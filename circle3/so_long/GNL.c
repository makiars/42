/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GNL.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:39:20 by marsenij          #+#    #+#             */
/*   Updated: 2024/09/26 08:48:22 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen(const char *s)
{
	int		len;
	char	*str;

	if (!s)
		return (0);
	str = (char *)s;
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*resize_buffer(char *buffer, int current_size)
{
	int		new_size;
	char	*new_buffer;
	int		i;

	i = 0;
	new_size = current_size * 2;
	new_buffer = (char *)malloc(new_size * sizeof(char));
	if (!new_buffer)
	{
		free (buffer);
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	while (i < current_size)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}


char	*read_until_newline(int fd, char *buffer, int *buffer_size, int *pos)
{
	char	ch;
	int		bytes_read;

	bytes_read = read(fd, &ch, 1);
	while (bytes_read > 0)
	{
		if (*pos >= *buffer_size - 1) 
		{
			buffer = resize_buffer(buffer, *buffer_size);
			*buffer_size *= 2;
		}
		buffer[(*pos)++] = ch;
		if (ch == '\n')
			break ;
		bytes_read = read(fd, &ch, 1);
	}
	if (bytes_read == 0 && *pos == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[*pos] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	int		buffer_size;
	int		pos;
	char	*buffer;

	if (fd < 0)
		return (NULL);
	buffer_size = 32;
	pos = 0;
	buffer = (char *)malloc(buffer_size * sizeof(char));
	if (!buffer)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	return (read_until_newline(fd, buffer, &buffer_size, &pos));
}