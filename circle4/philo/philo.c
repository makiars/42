/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/20 14:30:18 by marsenij         ###   ########.fr       */
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

void init_core(t_data *core, int argc, char **argv)
{
    int temp;
    int i;

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
    core->time_to_die = ft_atoi(argv[2]) * 1000;
    core->time_to_eat = ft_atoi(argv[3]) * 1000;
    core->time_to_sleep = ft_atoi(argv[4]) * 1000;
    if (argv[5] != NULL)
        core->has_to_eat_x = ft_atoi(argv[5]);
    core->someone_died = 0;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    core->start_time = ((get_time_us()/ 1000) * 1000);
}

void print_state(t_data *core, int philo, int state)
{
    uint64_t current_us = curr_time(core);
    int ms = current_us / 1000;
    char *msg;
    int sdied;
    
    pthread_mutex_lock(&core->died_mutex);
    sdied = core->someone_died;
    pthread_mutex_unlock(&core->died_mutex);
    if (state == DIED)
        msg = "died";
    else if (sdied == 0)
    {
        if (state == TAKEN_FORK)
            msg = "has taken a fork";
        else if (state == EATING)
            msg = "is eating";
        else if (state == SLEEPING)
            msg = "is sleeping";
        else if (state == THINKING)
            msg = "is thinking";   
        else
            return;
    }
    else
        return;

    pthread_mutex_lock(&core->print_mutex);
    printf("%d %d %s\n", ms, philo, msg);
    pthread_mutex_unlock(&core->print_mutex);

}


int	main(int argc, char **argv)
{
	t_data	core;

	init_core(&core, argc, argv);
	address_getter(&core);
	initialize_threads(&core);
	
}

void check_if_died(t_data *core, t_philo *philo) {
    uint64_t curr_time_us = curr_time(core);
    if (curr_time_us - philo->last_eaten >= core->time_to_die)
    {
        pthread_mutex_lock(&core->died_mutex);
        core->someone_died = 1;
        pthread_mutex_unlock(&core->died_mutex);
        
        philo->state = DIED;
        print_state(core, philo->id, philo->state);
        exit(0);
    }
}
