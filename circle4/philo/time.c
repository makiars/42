/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/02/17 16:23:38 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time_us(void)
{

	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec) * 1000000 + (uint64_t)(tv.tv_usec));
}

long long curr_time(t_data *core)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t now_us = tv.tv_sec * 1000000 + tv.tv_usec;
    return (now_us - core->start_time) / 1000;
}


void precise_sleep(uint64_t milliseconds)
{
    struct timeval start, current;
    uint64_t elapsed_us = 0;
    uint64_t target_us = milliseconds * 1000;

    gettimeofday(&start, NULL);
    while (elapsed_us < target_us)
    {
        usleep(10);
        gettimeofday(&current, NULL);
        elapsed_us = (current.tv_sec - start.tv_sec) * 1000000 +
                     (current.tv_usec - start.tv_usec);
    }
}

