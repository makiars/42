/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/21 12:45:35 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time_us(void)
{

	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec) * 1000000 + (uint64_t)(tv.tv_usec));
}

uint64_t curr_time(t_data *core) {
    uint64_t current_us = get_time_us();
    return (((current_us) / 1000) * 1000) - core->start_time;
}

void precise_sleep_with_curr_time(t_data *core, uint64_t target_us, t_philo *philo)
{
    uint64_t start_us = curr_time(core);
    (void) philo;
    while (curr_time(core) - start_us < target_us)
        usleep(100);
}
