/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/01/20 12:36:15 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(int ms, int philo, int state)
{
	if (state == 1)
		printf("%d %d has taken a fork\n", ms, philo);
	if (state == 2)
		printf("%d %d is eating\n", ms, philo);
	if (state == 3)
		printf("%d %d is sleeping\n", ms, philo);
	if (state == 4)
		printf("%d %d is thinking\n", ms, philo);
	if (state == 5)
		printf("%d %d died\n", ms, philo);
}

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

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec) * 1000 + (uint64_t)(tv.tv_usec) / 1000);
}

void	init_core(t_data *core, int argc, char **argv)
{
	int	temp;
	int	i;

	i = 1;
	temp = 0;
	if (argc < 5)
	{
		printf("not enough args\n");
		exit(2);
	}
	while (i < argc)
	{
		temp = ft_atoi(argv[i]);
		if (strcmp(ft_itoa(temp), argv[i]) != 0)
		{
			printf("use proper numbers, friend\n");
			exit(2);
		}
		i++;
	}
	core->num_philo = ft_atoi(argv[1]);
	core->time_to_die = ft_atoi(argv[2]);
	core->time_to_eat = ft_atoi(argv[3]);
	core->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		core->has_to_eat_x = ft_atoi(argv[5]);
	core->start_time = get_time_ms();
}

long long	curr_time(t_data	*core)
{
	return ((long long)get_time_ms() - core->start_time);
}

int	main(int argc, char **argv)
{
	t_data	core;

	(void) argc;
	init_core(&core, argc, argv);
	address_getter(&core);
	initialize_threads(&core);
	
	//printf("%lld\n", (long long)curr_time(&core));
}

