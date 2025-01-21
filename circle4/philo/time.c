/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/01/20 12:36:15 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec) * 1000 + (uint64_t)(tv.tv_usec) / 1000);
}

long long	curr_time(t_data	*core)
{
	return ((long long)get_time_ms() - core->start_time);
}

void precise_sleep(uint64_t milliseconds)
{
    struct timeval start, current;
    uint64_t elapsed_time = 0;

    gettimeofday(&start, NULL);

    while (elapsed_time < milliseconds)
    {
        usleep(10);
        gettimeofday(&current, NULL);

        elapsed_time = (current.tv_sec - start.tv_sec) * 1000 + 
                       (current.tv_usec - start.tv_usec) / 1000;
    }
}
