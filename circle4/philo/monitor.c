/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/27 15:40:48 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*meal_monitor(void *arg)
{
	t_data	*core;
	int		all_ate;
	t_philo	*p;
	int		i;

	i = 0;
	core = (t_data *)arg;
	while (1)
	{
		all_ate = 1;
		p = core->philo_head;
		while (i < core->num_philo)
		{
			if (p->ate_x < core->has_to_eat_x)
			{
				all_ate = 0;
				break ;
			}
			i++;
			p = p->next;
		}
		if (all_ate)
		{
			pthread_mutex_lock(&core->died_mutex);
			core->someone_died = 1;
			pthread_mutex_unlock(&core->died_mutex);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*death_monitor(void *arg)
{
	t_data		*core;
	t_philo		*curr;
	uint64_t	now;

	core = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&core->died_mutex);
		if (core->someone_died)
		{
			pthread_mutex_unlock(&core->died_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&core->died_mutex);
		curr = core->philo_head;
		while (curr)
		{
			now = curr_time(core);
			pthread_mutex_lock(&curr->meal_mutex);
			if (now - curr->last_eaten >= core->time_to_die)
			{
				pthread_mutex_unlock(&curr->meal_mutex);
				pthread_mutex_lock(&core->died_mutex);
				if (!core->someone_died)
				{
					core->someone_died = 1;
					pthread_mutex_lock(&core->print_mutex);
					printf("%lu %d died\n", now / 1000, curr->id);
					pthread_mutex_unlock(&core->print_mutex);
				}
				pthread_mutex_unlock(&core->died_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&curr->meal_mutex);
			curr = curr->next;
		}
		usleep(500);
	}
	return (NULL);
}




