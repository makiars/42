
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
		current->last_eaten = data->start_time;
		current->left_fork = &data->forks[i];
		current->right_fork = &data->forks[(i + 1) % data->num_philo];
		current->last_eaten = curr_time(address_getter(NULL));
		if (i == 0)
		{
			current->should_eat = 0;
			data->philo_head = current;
			current->prev = current;
			current->next = current;
		}
		else
		{
			current->prev = last;
				if (current->prev->should_eat == 0)
					current->should_eat = 1;
				else
					current->should_eat = 0;
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

	current = data->philo_head;
	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_create(&current->thread, NULL, philosopher_routine, current) != 0)
		{
			fprintf(stderr, "Error: Failed to create thread for philosopher %d.\n", current->id);
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
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

	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
}

void initialize_threads(t_data *data)
{
	malloc_and_init_mutex(data);
	init_philo(data);
	create_threads(data);
	join_threads(data);
	free_threads(data);
}
