/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/27 16:29:22 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*address_getter(t_data *data)
{
	static t_data	*new_core;

	if (data == NULL)
		return (new_core);
	else
	{
		new_core = data;
		return (new_core);
	}
}

void	print_state(t_data *data, int philo, int state)
{
	pthread_mutex_lock(&data->died_mutex);
	if (data->someone_died && state != DIED)
	{
		pthread_mutex_unlock(&data->died_mutex);
		return ;
	}
	pthread_mutex_lock(&data->print_mutex);
	if (state == TAKEN_FORK)
		printf("%lu %d has taken a fork\n", curr_time(data) / 1000, philo);
	else if (state == EATING)
		printf("%lu %d is eating\n", curr_time(data) / 1000, philo);
	else if (state == SLEEPING)
		printf("%lu %d is sleeping\n", curr_time(data) / 1000, philo);
	else if (state == THINKING)
		printf("%lu %d is thinking\n", curr_time(data) / 1000, philo);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(&data->died_mutex);
}

int	check_if_died(t_data *data)
{
	int	terminated;

	terminated = data->someone_died;
	pthread_mutex_lock(&data->died_mutex);
	terminated = data->someone_died;
	pthread_mutex_unlock(&data->died_mutex);
	return (terminated);
}
