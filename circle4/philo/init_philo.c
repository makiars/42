/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/27 17:27:09 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philosopher(t_data *data, int index)
{
	t_philo	*current;

	current = malloc(sizeof(t_philo));
	if (!current)
		return (NULL);
	current->id = index + 1;
	current->ate_x = 0;
	current->left_fork = &data->forks[index];
	current->right_fork = &data->forks[(index + 1) % data->num_philo];
	current->last_eaten = 0;
	pthread_mutex_init(&current->should_eat_mutex, NULL);
	pthread_mutex_init(&current->meal_mutex, NULL);
	return (current);
}

int	init_philo(t_data *data, t_philo *current, t_philo *last)
{
	int		i;

	last = NULL;
	i = -1;
	while (++i < data->num_philo)
	{
		current = create_philosopher(data, i);
		if (!current)
			return (0);
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
	return (i);
}
