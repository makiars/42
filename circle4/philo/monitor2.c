/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/04/03 10:38:25 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_has_eaten_enough(t_philo *p, t_data *data)
{
	int	has_eaten;

	has_eaten = 1;
	pthread_mutex_lock(&data->died_mutex);
	pthread_mutex_lock(&p->meal_mutex);
	if (p->ate_x < data->has_to_eat_x)
		has_eaten = 0;
	pthread_mutex_unlock(&data->died_mutex);
	pthread_mutex_unlock(&p->meal_mutex);
	return (has_eaten);
}

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
		if (!philo_has_eaten_enough(p, data))
		{
			all_ate = 0;
			break ;
		}
		i++;
		p = p->next;
		usleep(1000);
		if (data->threads_created == 0)
			return (-1);
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
		if (data->threads_created == 0)
			return (NULL);
	}
	return (NULL);
}
