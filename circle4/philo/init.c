/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/29 19:15:36 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_arg_positive(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 1)
	{
		printf("invalid philo input\n");
		return (0);
	}
	if (ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
	{
		printf("invalid \"time to X\"\n");
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		printf("invalid amount to eat\n");
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

int	input_handle(int argc, char **argv)
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
		i++;
	}
	return (0);
}

int	init_core(t_data *data, int argc, char **argv)
{
	struct timeval	tv;

	if (input_handle(argc, argv))
		return (1);
	if (pthread_mutex_init(&data->died_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
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
