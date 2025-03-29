/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/29 11:49:36 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_arg_positive(int argc, char **argv)
{
	(void) argc;

	if (ft_atoi(argv[1]) < 1)
	{
		printf("Less than 1 philo not possible\n");
		return (0);
	}
	if (ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
	{
		printf("Less than 1 time to X is impossible\n");
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		printf("Less than 1 eat amount impossible\n");
		return (0);
	}
	return (1);
}

int	validate_arg_count(int argc)
{
	if (argc < 5)
	{
		printf("not enough args\n");
		return (0);
	}
	else if (argc > 6)
	{
		printf("too many args\n");
		return (0);
	}
	return (1);
}

int	is_valid_number(char *arg)
{
	int		temp;
	char	*converted_str;

	temp = ft_atoi(arg);
	converted_str = ft_itoa(temp);
	if (!converted_str)
		return (0);

	if (ft_strcmp(converted_str, arg) != 0)
	{
		free(converted_str);
		return (0);
	}
	free(converted_str);
	return (1);
}

int	input_handle(int argc, char **argv, int temp)
{
	int	i;

	i = 1;
	if (!validate_arg_count(argc))
		return (1);
	if (!validate_arg_positive(argc, argv))
		return (1);


	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("use proper numbers, friend\n");
			return (1);
		}
		temp = ft_atoi(argv[i]);
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
