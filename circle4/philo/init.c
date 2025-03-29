/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/29 08:46:43 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_handle(int argc, char **argv, int temp)
{
	int				i;
	char			*str;

	i = 1;
	if (argc < 5)
	{
		printf("not enough args\n");
		return (1);
	}
	while (i < argc)
	{
		temp = ft_atoi(argv[i]);
		str = ft_itoa(temp);
		if (!str)
			return (0);
		if (ft_strcmp(str, argv[i]) != 0)
		{
			printf("use proper numbers, friend\n");
			free (str);
			return (1);
		}
		free (str);
		i++;
	}
	return (0);
}

int	init_core(t_data *data, int argc, char **argv)
{
	struct timeval	tv;
	int				temp;

	temp = 0;
	if (input_handle(argc, argv, temp))
		return (1);
	pthread_mutex_init(&data->died_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	data->has_to_eat_x = 0;
	if (argv[5] != NULL)
		data->has_to_eat_x = ft_atoi(argv[5]);
	data->someone_died = 0;
	gettimeofday(&tv, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init_core(&data, argc, argv))
		return (1);
	address_getter(&data);
	initialize_threads(&data);
}
