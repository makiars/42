/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/02/17 17:58:29 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void print_state(t_data *core, int philo, int state)
{
    int ms = curr_time(core);
    char *msg;

    if (state == TAKEN_FORK) msg = "has taken a fork";
    else if (state == EATING) msg = "is eating";
    else if (state == SLEEPING) msg = "is sleeping";
    else if (state == THINKING) msg = "is thinking";
    else if (state == DIED) msg = "died";
    else return;

    pthread_mutex_lock(&core->print_mutex);
    printf("%d %d %s\n", ms, philo, msg);
    pthread_mutex_unlock(&core->print_mutex);
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
	pthread_mutex_init(&core->print_mutex, NULL);
	core->num_philo = ft_atoi(argv[1]);
	core->time_to_die = ft_atoi(argv[2]);
	core->time_to_eat = ft_atoi(argv[3]);
	core->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		core->has_to_eat_x = ft_atoi(argv[5]);
	struct timeval tv;
	gettimeofday(&tv, NULL);
	core->start_time = get_time_us();

}

int	main(int argc, char **argv)
{
	t_data	core;

	init_core(&core, argc, argv);
	address_getter(&core);
	initialize_threads(&core);
	
}

