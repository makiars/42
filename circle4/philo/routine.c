
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

void p_eat(t_data *core, t_philo *philo)
{
	philo->last_eaten = curr_time(core);
	philo->state = EATING;
	print_state(core, philo->id, philo->state);

	precise_sleep(core->time_to_eat);
}

void p_release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);

    pthread_mutex_lock(&philo->next->should_eat_mutex);
    philo->next->should_eat = 1;
    pthread_mutex_unlock(&philo->next->should_eat_mutex);

    pthread_mutex_lock(&philo->should_eat_mutex);
    philo->should_eat = 0;
    pthread_mutex_unlock(&philo->should_eat_mutex);
}

void p_sleep(t_data *core, t_philo *philo)
{
	philo->state = SLEEPING;
	print_state(core, philo->id, philo->state);

	precise_sleep(core->time_to_sleep);
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data *core = address_getter(NULL);
	int	should_eat;

	while (1)
	{
		philo->state = THINKING;
		print_state(core, philo->id, philo->state);

        pthread_mutex_lock(&philo->should_eat_mutex);
        should_eat = philo->should_eat;
        pthread_mutex_unlock(&philo->should_eat_mutex);

		if (should_eat == 1)
		{
			p_take_fork(core, philo);
			p_eat(core, philo);
			p_release_fork(philo);
			p_sleep(core, philo);
		}
		else if ((uint64_t)core->time_to_die <  curr_time(core) - philo->last_eaten)
		{
			philo->state = DIED;
			print_state(core, philo->id, philo->state);
			exit(0);
		}
		else
			precise_sleep(core->time_to_eat);
	}
	return NULL;
}
