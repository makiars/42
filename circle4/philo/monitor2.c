/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/29 19:13:50 by marsenij         ###   ########.fr       */
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
		pthread_mutex_lock(&p->meal_mutex);
		if (p->ate_x < data->has_to_eat_x)
		{
			all_ate = 0;
			pthread_mutex_unlock(&data->died_mutex);
			pthread_mutex_unlock(&p->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->died_mutex);
		pthread_mutex_unlock(&p->meal_mutex);
		i++;
		p = p->next;
		usleep(1000);
	}
	return (all_ate);
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
