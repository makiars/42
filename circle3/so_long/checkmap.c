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

void	checksquare(int fd, int *rows, int *cols)
{
	char	*line;
	char	*temp;

	line = NULL;
	line = get_next_line(fd);//adjust get_next_line so it exits if malloc fails
	if (line == NULL)
	{
		write (2, "Map empty", 9);
		exit(EXIT_FAILURE);
	}
	*cols = ft_strlen(line);
	while (line)
	{
		temp = line;
		++(*rows);
		if (*cols != (int)ft_strlen(line))
		{
			if (*cols == (int)ft_strlen(line) + 1 && line[ft_strlen(line)] == '\0')
			{
				free(temp);
				break ;
			}	
			write(2, "Map not square\n", 15);
			free(line);
			exit(EXIT_FAILURE);
		}
		line = get_next_line(fd);
		free(temp);
	}
}

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

void	forbidden_letter(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\n' && map[i][j] != '\0')
		{
			if (map[i][j] != 'P' && map[i][j] != 'E' && map[i][j] != 'C' && map[i][j] != '0' && map[i][j] != '1')
			{
				free_map(map);
				write(1, "Wrong letters in Map\n", 21);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

int	checkwalls(char **map, int cols, int rows)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < cols)
	{
		if (map[0][j] != '1' || map[rows][j] != '1')
			return (0);
		j++;
	}
	j = 0;
	while (map[i] != NULL)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			return (0);
		i++;
	}
	return (1);

}

void	inputcheck(char **map, int cols, int rows)
{
	if (cntletter(map, 'P') != 1 || cntletter(map, 'E') != 1 || cntletter(map, 'C') < 1)
	{
		free_map(map);
		write(1, "Incorrect Player, Consumable or Exit number\n", 44);
		exit(EXIT_FAILURE);
	}
	if(!(checkwalls(map, (cols - 1), (rows - 1))))
	{
		free_map(map);
		write (1, "Walls wrong\n", 12);
		exit(EXIT_FAILURE);
	}
	forbidden_letter(map);
}

char	**parseinput(int fd, int rows, int cols)
{
	char	**map;
	int		i;

	i = -1;
	map = (char **)malloc((rows + 1) * (sizeof(char *)));
	if (map == NULL)
	{
		perror("Error allocating");
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
		perror("Error opening file");
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
