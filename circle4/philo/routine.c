/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/04/03 10:00:18 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_data *data, t_philo *philo)
{
	if (data->num_philo == 1)
	{
		printf("%lu 1 is thinking\n", curr_time(data) / 1000);
		pthread_mutex_lock(philo->left_fork);
		printf("%lu 1 has taken a fork\n", curr_time(data) / 1000);
		precise_sleep(data, data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		printf("%lu 1 died\n", curr_time(data) / 1000);
		pthread_mutex_lock(&data->died_mutex);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->died_mutex);
		return (0);
	}
	return (1);
}

int	check_death_condition(t_data *data)
{
	pthread_mutex_lock(&data->died_mutex);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->died_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->died_mutex);
	return (0);
}

void	handle_philosopher_cycle(t_data *data, t_philo *philo)
{
	philo->state = THINKING;
	print_state(data, philo->id, philo->state);
	if (philo->ate_x != 0 && data->num_philo % 2 != 0
		&& data->time_to_sleep < data->time_to_eat * 2)
		precise_sleep(data, data->time_to_eat * 2 - data->time_to_sleep);
	p_take_fork(data, philo);
	p_eat(data, philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->ate_x++;
	pthread_mutex_unlock(&philo->meal_mutex);
	p_release_fork(philo);
	p_sleep(data, philo);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	data = address_getter(NULL);
	philo = (t_philo *)arg;
	pthread_mutex_lock(&data->start_mutex);
	pthread_mutex_unlock(&data->start_mutex);
	if (!one_philo(data, philo))
		return (NULL);
	if (philo->id % 2 == 1)
		precise_sleep(data, 10000);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eaten = curr_time(data);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (data->threads_created == 0)
		return (NULL);
	while (1)
	{
		if (check_death_condition(data))
			return (NULL);
		handle_philosopher_cycle(data, philo);
	}
	return (NULL);
}
