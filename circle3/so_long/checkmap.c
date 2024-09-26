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
		if (*cols != (int)ft_strlen(line))//not sure if this quickfix is ok
		{
			write(2, "Map not square\n", 15);
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
		while (map[i][j] != '\n')
		{
			if (map[i][j] == ltr)
				cnt++;
			j++;
		}
		i++;
	}
	return (cnt);
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
	int	cntP;
	int	cntC;
	int	cntE;
	int	wallcheck;

	wallcheck = checkwalls(map, (cols - 1), (rows - 1));
	cntP = cntletter(map, 'P');
	cntE = cntletter(map, 'E');
	cntC = cntletter(map, 'C');
	if (cntP != 1 || cntE != 1 || cntC < 1)
	{
		write(1, "incorrect Player, Consumable or Exit number\n", 44);
		exit(EXIT_FAILURE);
	}
	//free doublearray
	if(!(wallcheck))
	{
		write (1, "Walls wrong\n", 12);
		exit(EXIT_FAILURE);
	}
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

void	get_map(int argc, char **argv, t_data *data)
{
	int		fd;
	int		rows;
	int		cols;
	char	**map;

	if (argc != 2)
		exit (EXIT_FAILURE);
	cols = 0;
	rows = 0;
	openfile(&fd, argv);
	checksquare(fd, &rows, &cols);
	close(fd);
	openfile(&fd, argv);
	map = parseinput(fd, rows, cols);
	close(fd);
	data->map = map;
	data->rows = rows;
	data->cols = cols - 1;
//	print_string_array(map);
}
