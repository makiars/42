/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/22 11:27:08 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "string.h"
# include "stdlib.h"
# include "stdio.h"
# include "unistd.h"
# include "pthread.h"
# include "sys/time.h"
# include "stdint.h"

typedef struct s_data
{
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		has_to_eat_x;
	uint64_t	start_time;
//add philospher specific stuff here in a seperate struc//add philospher specific stuff here in a seperate structt
}	t_data;


char	*ft_itoa(int n);
int	ft_atoi(const char *nptr);

#endif
