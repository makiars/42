/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/27 15:43:39 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_take_fork(t_data *core, t_philo *philo)
{
	philo->state = TAKEN_FORK;
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	print_state(core, philo->id, philo->state);
	print_state(core, philo->id, philo->state);
}

void	p_release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	p_eat(t_data *core, t_philo *philo)
{
	philo->last_eaten = curr_time(core);
	philo->state = EATING;
	print_state(core, philo->id, philo->state);
	precise_sleep_with_curr_time(core, core->time_to_eat);
}

void	p_sleep(t_data *core, t_philo *philo)
{
	philo->state = SLEEPING;
	print_state(core, philo->id, philo->state);
	precise_sleep_with_curr_time(core, core->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*core;

	philo = (t_philo *)arg;
	core = address_getter(NULL);
	pthread_mutex_lock(&core->start_mutex);
	pthread_mutex_unlock(&core->start_mutex);
	if (core->num_philo == 1)
	{
		print_state(core, philo->id, TAKEN_FORK);
		precise_sleep_with_curr_time(core, core->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 1)
		precise_sleep_with_curr_time(core, 10000);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eaten = curr_time(core);
	pthread_mutex_unlock(&philo->meal_mutex);
	while (1)
	{
		pthread_mutex_lock(&core->died_mutex);
		if (core->someone_died)
		{
			pthread_mutex_unlock(&core->died_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&core->died_mutex);
		philo->state = THINKING;
		print_state(core, philo->id, philo->state);
		if (philo->ate_x != 0 && core->num_philo % 2 != 0 &&
			core->time_to_sleep < core->time_to_eat * 2)
			precise_sleep_with_curr_time(core, core->time_to_eat * 2 -
				core->time_to_sleep);
		p_take_fork(core, philo);
		p_eat(core, philo);
		philo->ate_x++;
		p_release_fork(philo);
		p_sleep(core, philo);
	}
	return (NULL);
}
