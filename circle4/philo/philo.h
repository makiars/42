/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/01/06 12:34:01 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "string.h"
# include "stdlib.h"
# include "stdio.h"
# include "unistd.h"
# include "pthread.h"
# include "sys/time.h"
# include "stdint.h"

typedef struct s_data
{
	int			num_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			has_to_eat_x;
	uint64_t	start_time;
	t_philo		*head;
	//add philospher specific stuff here in a seperate struct
}	t_data;

typedef struct s_philo
{
	int				right_fork_state;
	uint64_t		last_eaten;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;


char	*ft_itoa(int n);
int		ft_atoi(const char *nptr);

#endif
