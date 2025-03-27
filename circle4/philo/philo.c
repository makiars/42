/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/27 12:48:19 by marsenij         ###   ########.fr       */
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
    char *str;

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
    if (argv[5] != NULL)
        core->has_to_eat_x = ft_atoi(argv[5]);
    core->someone_died = 0;
    struct timeval tv;
    gettimeofday(&tv, NULL);
}

void print_state(t_data *core, int philo, int state)
{
    char *msg;
    int sdied;
    char *ms_str;
    char *philo_str;
    
    pthread_mutex_lock(&core->died_mutex);
    sdied = core->someone_died;
    pthread_mutex_unlock(&core->died_mutex);
    if (state == DIED)
        msg = "died";
    if (sdied == 0)
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
    philo_str = ft_itoa(philo);
    ms_str=ft_itoa(curr_time(core)/1000);
    write(1, ms_str, ft_strlen(ms_str));
    write(1, " ", 1);
    write(1, philo_str, ft_strlen(philo_str));
    write(1, " ", 1);
    write(1, msg, ft_strlen(msg));
    write(1, "\n", 1);
    pthread_mutex_unlock(&core->print_mutex);
    free(ms_str);
    free(philo_str);

}


int	main(int argc, char **argv)
{
	t_data	core;

	init_core(&core, argc, argv);
	address_getter(&core);
	initialize_threads(&core);
	
}

int check_if_died(t_data *core, t_philo *philo) {
    uint64_t curr_time_us = curr_time(core);
    if (curr_time_us - philo->last_eaten >= core->time_to_die)
    {
        pthread_mutex_lock(&core->died_mutex);
        core->someone_died = 1;
        pthread_mutex_unlock(&core->died_mutex);
//        printf("Time to die %lu last eaten %lu curr time %lu\n ",core->time_to_die, philo->last_eaten, curr_time(core));
        philo->state = DIED;
        print_state(core, philo->id, philo->state);
        return(1);
    }
    return (0);
}
