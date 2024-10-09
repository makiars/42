/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:39:20 by marsenij          #+#    #+#             */
/*   Updated: 2024/09/26 08:48:22 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	cntletter(char **map, char ltr)
{
	int	i;
	int	cnt;
	int	j;

	j = 0;
	cnt = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\n' && map[i][j] != '\0')
		{
			if (map[i][j] == ltr)
				cnt++;
			j++;
		}
		i++;
	}
	return (cnt);
}

char	**parseinput(int fd, int rows, int cols)
{
	char	**map;
	int		i;

	i = -1;
	map = (char **)malloc((rows + 1) * (sizeof(char *)));
	if (map == NULL)
	{
		write(2, "Error\n", 6);
		write(2, "Malloc failed\n", 14);
		exit(EXIT_FAILURE);
	}
	while (++i < rows)
		map[i] = get_next_line(fd);
	map[i] = NULL;
	inputcheck(map, cols, rows);
	return (map);
}

void	openfile(int *fd, char **argv)
{
	*fd = open(argv[1], O_RDONLY);
	if (*fd == -1)
	{
		write(2, "Error\n", 6);
		write(2, "Opening file failed\n", 20);
		exit(EXIT_FAILURE);
	}
}

void	get_map(char **argv, t_data *data)
{
	int		fd;
	int		rows;
	int		cols;

	rows = 0;
	cols = 0;
	openfile(&fd, argv);
	checksquare(fd, &rows, &cols);
	close(fd);
	openfile(&fd, argv);
	data->map = parseinput(fd, rows, cols);
	close(fd);
	openfile(&fd, argv);
	data->flood_map = parseinput(fd, rows, cols);
	close(fd);
	data->rows = rows;
	data->cols = cols - 1;
}
