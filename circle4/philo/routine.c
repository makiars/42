
#include "philo.h"

void p_take_fork(t_data *core, t_philo *philo)
{
	philo->state = TAKEN_FORK;
	print_state(curr_time(core), philo->id, philo->state);
	pthread_mutex_lock(philo->left_fork);
	print_state(curr_time(core), philo->id, philo->state);
	pthread_mutex_lock(philo->right_fork);
}

void p_eat(t_data *core, t_philo *philo)
{
	philo->last_eaten = curr_time(core);
	philo->state = EATING;
	print_state(curr_time(core), philo->id, philo->state);
	precise_sleep(core->time_to_eat);
}

void p_release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->next->should_eat = 1;
	philo->should_eat = 0;
}

void p_sleep(t_data *core, t_philo *philo)
{
	philo->state = SLEEPING;
	print_state(curr_time(core), philo->id, philo->state);
	precise_sleep(core->time_to_sleep);
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data *core = address_getter(NULL);
	
	while (1)
	{
		philo->state = THINKING;
		print_state(curr_time(core) , philo->id, philo->state);
		//printf("philonum:%d curr:%llu last_eaten:%lu\n", philo->id,curr_time(core), philo->last_eaten);
		if (philo->should_eat == 1)
		{
			p_take_fork(core, philo);
			p_eat(core, philo);
			p_release_fork(philo);
			p_sleep(core, philo);
		}
		else if ((uint64_t)core->time_to_die <  curr_time(core) - philo->last_eaten)
		{
			philo->state = DIED;
			print_state(curr_time(core) , philo->id, DIED);
			exit(0);
		}
		else
			precise_sleep(core->time_to_eat);


	}
	return NULL;
}
