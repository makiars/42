/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/29 19:11:50 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_someone_died(t_data *data)
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

int	died(t_data *data, uint64_t now, t_philo *curr)
{
	pthread_mutex_lock(&data->died_mutex);
	if (!data->someone_died)
	{
		data->someone_died = 1;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lu %d died\n", now / 1000, curr->id);
		pthread_mutex_unlock(&data->print_mutex);
	}
	pthread_mutex_unlock(&data->died_mutex);
	return (1);
}

int	check_philosopher_death(t_data *data, t_philo *head)
{
	t_philo		*curr;
	uint64_t	now;
	uint64_t	last;
	int			i;

	curr = head;
	now = get_time_us() - data->start_time;
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&curr->meal_mutex);
		last = curr->last_eaten;
		pthread_mutex_unlock(&curr->meal_mutex);
		if (now - last >= data->time_to_die)
		{
			died(data, now, curr);
			return (1);
		}
		curr = curr->next;
		i++;
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	t_philo	*curr;

	data = (t_data *)arg;
	curr = data->philo_head;
	pthread_mutex_lock(&data->start_mutex);
	pthread_mutex_unlock(&data->start_mutex);
	while (1)
	{
		if (check_someone_died(data))
			return (NULL);
		if (check_philosopher_death(data, curr))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
