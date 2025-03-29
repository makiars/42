/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/29 12:53:28 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec) * 1000000 + (uint64_t)(tv.tv_usec));
}

uint64_t	curr_time(t_data *data)
{
	uint64_t	current_us;

	current_us = get_time_us();
	return ((((current_us) / 1000) * 1000) - data->start_time);
}

void	precise_sleep(t_data *data, uint64_t target_us)
{
	uint64_t	start_us;

	start_us = curr_time(data);
	while (curr_time(data) - start_us < target_us)
	{
		if (check_if_died(data))
			return ;
		usleep(100);
	}
}
