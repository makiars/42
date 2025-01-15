#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>

// Define structs as provided
typedef struct s_philo
{
	pthread_t        thread;
	int              id;
	int              ate_x;
	pthread_mutex_t  *right_fork;
	pthread_mutex_t  *left_fork;
	uint64_t         last_eaten;
	int              state;
	struct s_philo   *next;
	struct s_philo   *prev;
} t_philo;

typedef struct s_data
{
	int             num_philo;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             has_to_eat_x;
	uint64_t        start_time;
	t_philo         *philo_head;
	pthread_mutex_t *forks;
} t_data;

// Function prototypes
uint64_t get_time(void);
void *philosopher_routine(void *arg);
void initialize_threads(t_data *data);

uint64_t get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (1)
	{
		// Simulate thinking
		printf("Philosopher %d is thinking.\n", philo->id);
		usleep(1000 * 500); // Simulate time for thinking

		// Take forks
		pthread_mutex_lock(philo->left_fork);
		printf("Philosopher %d picked up left fork.\n", philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("Philosopher %d picked up right fork.\n", philo->id);

		// Simulate eating
		philo->last_eaten = get_time();
		printf("Philosopher %d is eating.\n", philo->id);
		usleep(1000 * 500); // Simulate time for eating

		// Release forks
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf("Philosopher %d put down forks.\n", philo->id);

		// Simulate sleeping
		printf("Philosopher %d is sleeping.\n", philo->id);
		usleep(1000 * 500); // Simulate time for sleeping
	}
	return NULL;
}

void initialize_threads(t_data *data)
{
	int i;
	t_philo *current;

	// Allocate memory for philosophers and forks
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!(data->forks))
	{
		fprintf(stderr, "Error: Failed to allocate memory for forks.\n");
		exit(EXIT_FAILURE);
	}

	// Initialize forks
	for (i = 0; i < data->num_philo; i++)
		pthread_mutex_init(&data->forks[i], NULL);

	// Initialize philosophers
	for (i = 0; i < data->num_philo; i++)
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
		current->next = (i == data->num_philo - 1) ? data->philo_head : NULL;
		if (data->philo_head)
		{
			current->prev = data->philo_head->prev;
			data->philo_head->prev->next = current;
			data->philo_head->prev = current;
		}
		else
		{
			data->philo_head = current;
			current->prev = current;
			current->next = current;
		}
	}

	// Start philosopher threads
	current = data->philo_head;
	for (i = 0; i < data->num_philo; i++)
	{
		if (pthread_create(&current->thread, NULL, philosopher_routine, current) != 0)
		{
			fprintf(stderr, "Error: Failed to create thread for philosopher %d.\n", current->id);
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}

	// Join philosopher threads (in this simulation, they run indefinitely)
	current = data->philo_head;
	for (i = 0; i < data->num_philo; i++)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}

	// Free resources
	for (i = 0; i < data->num_philo; i++)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
}
