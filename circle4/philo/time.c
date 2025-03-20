/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/20 18:16:50 by marsenij         ###   ########.fr       */
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
    return ((current_us / 1000) * 1000) - core->start_time;
}

void precise_sleep_with_curr_time(t_data *core, uint64_t target_us, t_philo *philo)
{
    uint64_t start_us = curr_time(core);
    volatile uint64_t elapsed, rem;
    
 
    elapsed = curr_time(core) - start_us;
    while (elapsed < target_us)
    {
        rem = target_us - elapsed;
        if (rem > 1500)
        {
            check_if_died(core, philo);
            usleep(rem/2);
        }
        else
        {
            while (curr_time(core) - start_us < target_us)
                ;
            break;
        }
        elapsed = curr_time(core) - start_us;
    }
}
