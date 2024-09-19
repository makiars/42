/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:44:51 by marsenij          #+#    #+#             */
/*   Updated: 2024/05/30 11:54:51 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*store;
	char		*res;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (leftover)
		store = ft_strdup(leftover);
	else
		store = ft_strdup("");
	freeme(&leftover);
	if (!store)
		return (NULL);
	store = read_and_store(fd, store, leftover);
	if (!store)
		return (NULL);
	res = ft_substr(store, 0, ft_linelen(store) + 1);
	if (!res)
		return (freeme(&store), NULL);
	if (store[ft_linelen(store)] == '\n')
		leftover = ft_substr(store, ft_linelen(store) + 1, BUFFER_SIZE);
	else
		freeme(&leftover);
	return (freeme(&store), res);
}

char	*read_and_store(int fd, char *store, char *leftover)
{
	int		charsread;
	char	*buf;
	char	*temp;

	while (!ft_strchr(store, '\n'))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (freeme(&store), NULL);
		charsread = read(fd, buf, BUFFER_SIZE);
		if (charsread == -1)
			return (freeme(&buf), freeme(&store), NULL);
		else if (charsread == 0 && store[0] == '\0')
			return (freeme(&leftover), freeme(&buf), freeme(&store), NULL);
		else if (charsread == 0)
			return (freeme(&buf), store);
		buf[charsread] = '\0';
		temp = ft_strjoin(store, buf);
		freeme(&buf);
		if (!temp)
			return (freeme(&store), NULL);
		store = temp;
	}
	return (store);
}

void	freeme(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	ft_linelen(char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\n' && s[len])
		len++;
	return (len);
}

/*
  #include <fcntl.h> // for open/close functions
#include <stdio.h> // for printf

int main(void)
{
    int     fd;
    char    *line;

    fd = open("text.txt", O_RDWR);
    if (fd == -1)
        return (-1);
    line = get_next_line(fd);

    while (line)
    {
        printf("[%s]\n", line);
        free(line);
        line = get_next_line(fd);
    }
    printf("[%s]\n", line);
    close(fd);
}
*/
