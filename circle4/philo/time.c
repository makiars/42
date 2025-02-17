/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/02/17 17:36:55 by marsenij         ###   ########.fr       */
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
    return ((now_us - core->start_time) / 1000);
}

void precise_sleep_with_curr_time(t_data *core, uint64_t milliseconds)
{
    uint64_t start_ms = curr_time(core);
    uint64_t target_ms = start_ms + milliseconds;

    while (curr_time(core) < target_ms)
    {
        uint64_t remaining_ms = target_ms - curr_time(core);
        if (remaining_ms > 1)
            usleep((remaining_ms - 1) * 1000); // sleep in chunks
    }
}





