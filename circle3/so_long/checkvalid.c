/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkvalid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:39:20 by marsenij          #+#    #+#             */
/*   Updated: 2024/09/26 08:48:22 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	checksquare_loop(int fd, int *rows, int *cols, char *line)
{
	char	*temp;

	while (line)
	{
		temp = line;
		++(*rows);
		if (*cols != (int)ft_strlen(line))
		{
			if (*cols == (int)ft_strlen(line)
				+ 1 && line[ft_strlen(line)] == '\0')
			{
				free(temp);
				break ;
			}
			write(2, "Error\n", 6);
			write(2, "Map not square\n", 15);
			free(line);
			exit(EXIT_FAILURE);
		}
		line = get_next_line(fd);
		free(temp);
	}
}

void	checksquare(int fd, int *rows, int *cols)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		write(2, "Error\n", 6);
		write (2, "Map empty\n", 10);
		exit(EXIT_FAILURE);
	}
	*cols = ft_strlen(line);
	checksquare_loop(fd, rows, cols, line);
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
			if (map[i][j] != 'P' && map[i][j] != 'E' && map[i][j] != 'C'
				&& map[i][j] != '0' && map[i][j] != '1')
			{
				free_map(map);
				write(2, "Error\n", 6);
				write(2, "Wrong letters in Map\n", 21);
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
	if (cntletter(map, 'P') != 1 || cntletter(map, 'E') != 1
		|| cntletter(map, 'C') < 1)
	{
		free_map(map);
		write(2, "Error\n", 6);
		write(1, "Incorrect Player, Consumable or Exit number\n", 44);
		exit(EXIT_FAILURE);
	}
	if (!(checkwalls(map, (cols - 1), (rows - 1))))
	{
		free_map(map);
		write(2, "Error\n", 6);
		write (1, "Walls wrong\n", 12);
		exit(EXIT_FAILURE);
	}
	forbidden_letter(map);
}
