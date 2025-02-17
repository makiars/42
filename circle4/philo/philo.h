/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/02/17 17:37:12 by marsenij         ###   ########.fr       */
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

#  define TAKEN_FORK 1
#  define EATING 2
#  define SLEEPING 3
#  define THINKING 4
#  define DIED 5

typedef struct s_philo
{
	pthread_t			thread;		
	int					id;
	int					ate_x;
	int					has_died;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	uint64_t			last_eaten;
	int					state;
	pthread_mutex_t		should_eat_mutex;
	int					should_eat;
	struct s_philo		*next;
	struct s_philo		*prev;
}	t_philo;

typedef struct s_data
{
	int			num_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			has_to_eat_x;
	uint64_t	start_time;
	t_philo		*philo_head;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
}	t_data;



char		*ft_itoa(int n);
int			ft_atoi(const char *nptr);
void		initialize_threads(t_data *data);
t_data		*address_getter(t_data *core);
uint64_t	get_time_us(void);
void		print_state(t_data *core, int philo, int state);
uint64_t	curr_time(t_data *core);
//void		precise_sleep(uint64_t milliseconds);
void		precise_sleep_with_curr_time(t_data *core, uint64_t milliseconds);
void *philosopher_routine(void *arg);



#endif
