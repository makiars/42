/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/04/03 10:34:59 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	create_death_thread(t_data *data)
{
	pthread_t	death_monitor_thread;

	if (data->num_philo > 1)
	{
		if (pthread_create(&death_monitor_thread, NULL,
				death_monitor, data) != 0)
		{
			return (0);
		}
		return (death_monitor_thread);
	}
	return (1);
}

pthread_t	create_meal_thread(t_data *data)
{
	pthread_t	meal_monitor_thread;

	if (data->has_to_eat_x > 0)
	{
		if (pthread_create(&meal_monitor_thread, NULL, meal_monitor, data) != 0)
		{
			return (0);
		}
		return (meal_monitor_thread);
	}
	return (1);
}

int	initialize_philosopher_threads(t_data *data)
{
	int		i;
	t_philo	*current;

	data->threads_created = 0;
	data->start_time = (((get_time_us()) / 1000) * 1000);
	current = data->philo_head;
	pthread_mutex_lock(&data->start_mutex);
	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_create(&current->thread, NULL,
				philosopher_routine, current) != 0)
			return (i);
		current = current->next;
	}
	return (-1);
}

void	cleanup_failed_threads(t_data *data, int created_threads)
{
	t_philo	*current;
	int		i;

	pthread_mutex_unlock(&data->start_mutex);
	current = data->philo_head;
	i = 0;
	while (i++ < created_threads)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}
	destroy_mutex(data);
}

int	create_monitor_threads(t_data *data)
{
	data->meal_monitor_thread = create_meal_thread(data);
	if (!data->meal_monitor_thread)
		return (0);
	data->death_monitor_thread = create_death_thread(data);
	if (!data->death_monitor_thread)
		return (0);
	return (1);
}
