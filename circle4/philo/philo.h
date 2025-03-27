/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2025/03/27 15:05:28 by marsenij         ###   ########.fr       */
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
# include "./ft_printf/ft_printf.h"

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
	pthread_mutex_t		meal_mutex;
	struct s_philo		*next;
	struct s_philo		*prev;
}	t_philo;

typedef struct s_data
{
    int                 num_philo;
    uint64_t            time_to_die;
    uint64_t            time_to_eat;
    uint64_t            time_to_sleep;
    int                 has_to_eat_x;
    uint64_t            start_time;
    t_philo             *philo_head;
    pthread_mutex_t     *forks;
    pthread_mutex_t     print_mutex;
	pthread_mutex_t     died_mutex;
    pthread_mutex_t     start_mutex;
	volatile int		someone_died;
	int					threads_created;
}   t_data;





char		*ft_itoa(int n);
int			ft_atoi(const char *nptr);
void		initialize_threads(t_data *data);
t_data		*address_getter(t_data *core);
uint64_t	get_time_us(void);
void		print_state(t_data *core, int philo, int state);
uint64_t	curr_time(t_data *core);
void		precise_sleep_with_curr_time(t_data *core, uint64_t milliseconds, t_philo *philo);
void		*philosopher_routine(void *arg);
int			check_if_died(t_data *core, t_philo *philo);
void		p_release_fork(t_philo *philo);
void 		*death_monitor(void *arg);
void		*meal_monitor(void *arg);
#endif
