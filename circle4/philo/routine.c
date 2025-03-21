
#include "philo.h"

void p_take_fork(t_data *core, t_philo *philo)
{
	philo->state = TAKEN_FORK;

	if (philo->left_fork < philo->right_fork) 
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	print_state(core, philo->id, philo->state);
	print_state(core, philo->id, philo->state);


}

void p_release_fork(t_philo *philo)
{
//	if (philo->left_fork < philo->right_fork) 
//	{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);  
/*    }
	else
	{
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    }*/
}

void p_eat(t_data *core, t_philo *philo)
{
    philo->last_eaten = curr_time(core);
    philo->state = EATING;
    print_state(core, philo->id, philo->state);
    precise_sleep_with_curr_time(core, core->time_to_eat, philo);
}

void p_sleep(t_data *core, t_philo *philo)
{
    philo->state = SLEEPING;
    print_state(core, philo->id, philo->state);
    precise_sleep_with_curr_time(core, core->time_to_sleep, philo);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data *core = address_getter(NULL);


    
    if (philo->start_delay)
        precise_sleep_with_curr_time(core, get_time_us() + philo->start_delay, philo);

    philo->last_eaten = curr_time(core);
    while (1)
    {
        check_if_died(core, philo);
        philo->state = THINKING;
        print_state(core, philo->id, philo->state);
        if (philo->ate_x != 0 && core->num_philo %2 !=0 && core->time_to_sleep < core->time_to_eat *2)
            precise_sleep_with_curr_time(core, core->time_to_eat * 2 - core->time_to_sleep, philo);
        check_if_died(core, philo);
        p_take_fork(core, philo);
        check_if_died(core, philo);
        p_eat(core, philo);
        philo->ate_x++;
        check_if_died(core, philo);
        p_release_fork(philo);
        check_if_died(core, philo);
        p_sleep(core, philo);

    }
    return NULL;
}
