
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
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void p_eat(t_data *core, t_philo *philo)
{
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_eaten = curr_time(core);
    pthread_mutex_unlock(&philo->meal_mutex);
    philo->state = EATING;
    print_state(core, philo->id, philo->state);
    precise_sleep_with_curr_time(core, core->time_to_eat);
}

void p_sleep(t_data *core, t_philo *philo)
{
    philo->state = SLEEPING;
    print_state(core, philo->id, philo->state);
    precise_sleep_with_curr_time(core, core->time_to_sleep);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data *core = address_getter(NULL);

    while (core->start_flag == 0)
        usleep(100);
    while (1)
    {
        check_if_died(core, philo);
        if (philo->id % 2 != 0)
        {
            uint64_t desired_start = philo->last_eaten + philo->start_delay;
            uint64_t now = curr_time(core);
            if (now < desired_start)
                precise_sleep_with_curr_time(core, desired_start - now);
        }
        philo->state = THINKING;
        print_state(core, philo->id, philo->state);
        if (core->time_to_die < curr_time(core) - philo->last_eaten)
        {
            philo->state = DIED;
            print_state(core, philo->id, philo->state);
            exit(0);
        }
        check_if_died(core, philo);
        p_take_fork(core, philo);
        check_if_died(core, philo);
        p_eat(core, philo);
        check_if_died(core, philo);
        p_release_fork(philo);
        check_if_died(core, philo);
        p_sleep(core, philo);
    }
    return NULL;
}
