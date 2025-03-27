/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/27 15:14:55 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*address_getter(t_data *core)
{
	static t_data	*new_core;

	if (core == NULL)
		return (new_core);
	else
	{
		new_core = core;
		return (new_core);
	}
}

void	init_core(t_data *core, int argc, char **argv)
{
	int				temp;
	int				i;
	char			*str;
	struct timeval	tv;

	i = 1;
	temp = 0;
	if (argc < 5)
	{
		ft_printf("not enough args\n");
		exit(2);
	}
	while (i < argc)
	{
		temp = ft_atoi(argv[i]);
		str = ft_itoa(temp);
		if (strcmp(str, argv[i]) != 0)
		{
			ft_printf("use proper numbers, friend\n");
			free (str);
			exit(2);
		}
		free (str);
		i++;
	}
	pthread_mutex_init(&core->died_mutex, NULL);
	pthread_mutex_init(&core->print_mutex, NULL);
	core->num_philo = ft_atoi(argv[1]);
	core->time_to_die = ft_atoi(argv[2]) * 1000;
	core->time_to_eat = ft_atoi(argv[3]) * 1000;
	core->time_to_sleep = ft_atoi(argv[4]) * 1000;
	core->has_to_eat_x = 0;
	if (argv[5] != NULL)
		core->has_to_eat_x = ft_atoi(argv[5]);
	core->someone_died = 0;
	gettimeofday(&tv, NULL);
}

void	print_state(t_data *core, int philo, int state)
{
	pthread_mutex_lock(&core->died_mutex);
	if (core->someone_died && state != DIED)
	{
		pthread_mutex_unlock(&core->died_mutex);
		return ;
	}
	pthread_mutex_lock(&core->print_mutex);
	if (state == TAKEN_FORK)
		printf("%lu %d has taken a fork\n", curr_time(core) / 1000, philo);
	else if (state == EATING)
		printf("%lu %d is eating\n", curr_time(core) / 1000, philo);
	else if (state == SLEEPING)
		printf("%lu %d is sleeping\n", curr_time(core) / 1000, philo);
	else if (state == THINKING)
		printf("%lu %d is thinking\n", curr_time(core) / 1000, philo);
	pthread_mutex_unlock(&core->print_mutex);
	pthread_mutex_unlock(&core->died_mutex);
}

int	main(int argc, char **argv)
{
	t_data	core;

	init_core(&core, argc, argv);
	address_getter(&core);
	initialize_threads(&core);
}

int	check_if_died(t_data *core)
{
	int	terminated;

	terminated = core->someone_died;
	pthread_mutex_lock(&core->died_mutex);
	terminated = core->someone_died;
	pthread_mutex_unlock(&core->died_mutex);
	return (terminated);
}
