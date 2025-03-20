/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/20 10:37:08 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time_us(void)
{

	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec) * 1000000 + (uint64_t)(tv.tv_usec));
}

uint64_t curr_time(t_data *core)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t now_us = tv.tv_sec * 1000000 + tv.tv_usec;
    return (now_us - core->start_time);
}

void precise_sleep_with_curr_time(t_data *core, uint64_t milliseconds)
{
    (void) core;
    uint64_t start_us = get_time_us();
    uint64_t target_us = milliseconds * 1000;
    volatile uint64_t elapsed, rem;

    while ((elapsed = get_time_us() - start_us) < target_us)
    {
        //add alive check
        rem = target_us - elapsed;
        if (rem > 1000)
            usleep(rem / 2);
        else
        {
            usleep(10);
        }
    }
}







