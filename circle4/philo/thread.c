/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/29 19:04:22 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_and_init_mutex(t_data *data)
{
	int		i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!(data->forks))
		return (0);
	i = -1;
	while (++i < data->num_philo)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
	if (pthread_mutex_init(&data->start_mutex, NULL) != 0)
		return (0);
	return (1);
}

int	create_threads(t_data *data)
{
	int			i;
	t_philo		*current;

	data->threads_created = 0;
	data->start_time = (((get_time_us()) / 1000) * 1000);
	current = data->philo_head;
	pthread_mutex_lock(&data->start_mutex);
	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_create(&current->thread, NULL,
				philosopher_routine, current) != 0)
			return (0);
		current = current->next;
	}
	data->meal_monitor_thread = create_meal_thread(data);
	if (!data->meal_monitor_thread)
		return (0);
	data->death_monitor_thread = create_death_thread(data);
	if (!data->death_monitor_thread)
		return (0);
	pthread_mutex_unlock(&data->start_mutex);
	return (1);
}

void	join_threads(t_data *data)
{
	int		i;
	t_philo	*current;

	current = data->philo_head;
	i = -1;
	while (++i < data->num_philo)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}
}

void	free_threads(t_data *data)
{
	int		i;
	t_philo	*current;
	t_philo	*next;

	current = data->philo_head;
	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	i = -1;
	while (++i < data->num_philo)
	{
		pthread_mutex_destroy(&current->should_eat_mutex);
		pthread_mutex_destroy(&current->meal_mutex);
		next = current->next;
		free(current);
		current = next;
	}
	pthread_mutex_destroy(&data->start_mutex);
	pthread_mutex_destroy(&data->died_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}

void	initialize_threads(t_data *data)
{
	t_philo		*current;
	t_philo		*last;

	last = NULL;
	current = NULL;
	if (!malloc_and_init_mutex(data))
		return ;
	if (!init_philo(data, current, last))
		return ;
	if (!create_threads(data))
		return ;
	join_threads(data);
	if (data->num_philo > 1)
		pthread_join(data->death_monitor_thread, NULL);
	if (data->has_to_eat_x > 0)
		pthread_join(data->meal_monitor_thread, NULL);
	free_threads(data);
}
