/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/27 15:43:14 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	malloc_and_init_mutex(t_data *data)
{
	int		i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!(data->forks))
	{
		fprintf(stderr, "Error: Failed to allocate memory for forks.\n");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
}

void	init_philo(t_data *data)
{
	int		i;
	t_philo	*current;
	t_philo	*last;

	last = NULL;
	i = -1;
	while (++i < data->num_philo)
	{
		current = malloc(sizeof(t_philo));
		if (!current)
		{
			fprintf(stderr, "Error: Failed to allocate memory for philosopher.\n");
			exit(EXIT_FAILURE);
		}
		current->id = i + 1;
		current->ate_x = 0;
		current->left_fork = &data->forks[i];
		current->right_fork = &data->forks[(i + 1) % data->num_philo];
		current->last_eaten = 0;
		pthread_mutex_init(&current->should_eat_mutex, NULL);
		pthread_mutex_init(&current->meal_mutex, NULL);
		if (i == 0)
		{
			data->philo_head = current;
			current->prev = current;
			current->next = current;
		}
		else
		{
			current->prev = last;
			last->next = current;
			current->next = data->philo_head;
			data->philo_head->prev = current;
		}
		last = current;
	}
}

void	create_threads(t_data *data)
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
		{
			fprintf(stderr, "Error: Failed to create thread for philosopher %d.\n", current->id);
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
	pthread_mutex_unlock(&data->start_mutex);
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
		next = current->next;
		free(current);
		current = next;
	}
	pthread_mutex_destroy(&data->start_mutex);
}

pthread_t	create_death_thread(t_data *data)
{
	pthread_t	death_monitor_thread;

	if (data->num_philo > 1)
	{
		if (pthread_create(&death_monitor_thread, NULL,
				death_monitor, data) != 0)
		{
			fprintf(stderr, "Error: Failed to create death monitor thread.\n");
			return (0);
		}
		return (death_monitor_thread);
	}
	return (0);
}

pthread_t	create_meal_thread(t_data *data)
{
	pthread_t	meal_monitor_thread;

	if (data->has_to_eat_x > 0)
	{
		if (pthread_create(&meal_monitor_thread, NULL, meal_monitor, data) != 0)
		{
			fprintf(stderr, "Error: Failed to create meal monitor thread.\n");
			return (0);
		}
		return (meal_monitor_thread);
	}
	return (0);
}

void	initialize_threads(t_data *data)
{
	pthread_t	death_monitor_thread;
	pthread_t	meal_monitor_thread;

	malloc_and_init_mutex(data);
	init_philo(data);
	create_threads(data);
	meal_monitor_thread = create_meal_thread(data);
	death_monitor_thread = create_death_thread(data);
	join_threads(data);
	if (data->num_philo > 1)
		pthread_join(death_monitor_thread, NULL);
	if (data->has_to_eat_x > 0)
		pthread_join(meal_monitor_thread, NULL);
	free_threads(data);
}
