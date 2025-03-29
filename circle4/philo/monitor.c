/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/29 12:35:01 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_philosophers_ate(t_data *data)
{
	int		i;
	int		all_ate;
	t_philo	*p;

	i = 0;
	all_ate = 1;
	p = data->philo_head;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->died_mutex);
		if (p->ate_x < data->has_to_eat_x)
		{
			all_ate = 0;
			pthread_mutex_unlock(&data->died_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->died_mutex);
		i++;
		p = p->next;
		usleep(1000);
	}
	return (all_ate);
}

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

void	*meal_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;

	pthread_mutex_lock(&data->start_mutex);
	pthread_mutex_unlock(&data->start_mutex);

	while (1)
	{
		if (check_all_philosophers_ate(data))
		{
			pthread_mutex_lock(&data->died_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->died_mutex);
			break ;
		}
		if (check_someone_died(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}

int	check_philosopher_death(t_data *data, t_philo *curr)
{
	uint64_t	now;

	while (curr)
	{
		now = curr_time(data);
		pthread_mutex_lock(&curr->meal_mutex);
		if (now - curr->last_eaten >= data->time_to_die)
		{
			pthread_mutex_unlock(&curr->meal_mutex);
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
		pthread_mutex_unlock(&curr->meal_mutex);
		curr = curr->next;
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
