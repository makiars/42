
#include "philo.h"

void malloc_and_init_mutex(t_data *data)
{
	int		i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!(data->forks))
	{
		fprintf(stderr, "Error: Failed to allocate memory for forks.\n");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_init(&data->forks[i], NULL);

	pthread_mutex_init(&data->start_mutex, NULL);
}

void init_philo(t_data *data)
{
	int	i;
	t_philo	*current;
	t_philo	*last = NULL;

	i = -1;
	while (++i < data->num_philo)
	{
		current = malloc(sizeof(t_philo));
		if (!current)
		{
			fprintf(stderr, "Error: Failed to allocate memory for philosopher.\n");
			exit(EXIT_FAILURE);
		}
		current->id = i + 1;
		current->ate_x = 0;
		current->left_fork = &data->forks[i];
		current->right_fork = &data->forks[(i + 1) % data->num_philo];
		current->last_eaten = curr_time(address_getter(NULL));
		pthread_mutex_init(&current->should_eat_mutex, NULL);
		if (current->id == data->num_philo && data->num_philo % 2 != 0)
			current->start_delay = data->time_to_eat *2;
		else if ((current->id % 2) != 0)
            current->start_delay = data->time_to_eat;
        else
            current->start_delay = 0;
		if (i == 0)
		{
			data->philo_head = current;
			current->prev = current;
			current->next = current;
		}
		else
		{
			current->prev = last;
			last->next = current;
			current->next = data->philo_head;
			data->philo_head->prev = current;
		}
		last = current;
	}
}

void create_threads(t_data *data)
{
	int		i;
	t_philo *current;

	
	pthread_mutex_lock(&data->start_mutex);
	
	current = data->philo_head;
	i = -1;
	while (++i < data->num_philo)
	{
		current->last_eaten = data->start_time;
		if (pthread_create(&current->thread, NULL, philosopher_routine, current) != 0)
		{
			fprintf(stderr, "Error: Failed to create thread for philosopher %d.\n", current->id);
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
	data->start_time = ((get_time_us()/ 1000) * 1000);
	pthread_mutex_unlock(&data->start_mutex);
}

void join_threads(t_data *data)
{
	int		i;
	t_philo *current;

	current = data->philo_head;
	i = -1;
	while (++i < data->num_philo)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}
}

void free_threads(t_data *data)
{
	int		i;
	t_philo *current = data->philo_head;

	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	i = -1;
    while (++i < data->num_philo)
    {
        pthread_mutex_destroy(&current->should_eat_mutex);
        t_philo *next = current->next;
        free(current);
        current = next;
    }
	pthread_mutex_destroy(&data->start_mutex);
}

void initialize_threads(t_data *data)
{
	malloc_and_init_mutex(data);
	init_philo(data);
	create_threads(data);
	join_threads(data);
	free_threads(data);
}
