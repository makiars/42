/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/29 12:41:37 by marsenij         ###   ########.fr       */
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
