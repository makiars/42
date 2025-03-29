/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/29 12:54:08 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_take_fork(t_data *data, t_philo *philo)
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
	print_state(data, philo->id, philo->state);
	print_state(data, philo->id, philo->state);
}

void	p_release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	p_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->died_mutex);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->died_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->died_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eaten = curr_time(data);
	pthread_mutex_unlock(&philo->meal_mutex);
	philo->state = EATING;
	print_state(data, philo->id, philo->state);
	precise_sleep(data, data->time_to_eat);
}

void	p_sleep(t_data *data, t_philo *philo)
{
	philo->state = SLEEPING;
	print_state(data, philo->id, philo->state);
	precise_sleep(data, data->time_to_sleep);
}
