#include "philo.h"

void *meal_monitor(void *arg)
{
    t_data *core = (t_data *)arg;
    int all_ate;
    t_philo *p;

    while (1)
    {
        all_ate = 1;
        p = core->philo_head;
        for (int i = 0; i < core->num_philo; i++)
        {
            if (p->ate_x < core->has_to_eat_x)
            {
                all_ate = 0;
                break;
            }
            p = p->next;
        }
        if (all_ate)
        {
            pthread_mutex_lock(&core->died_mutex);
            core->someone_died = 1;
            pthread_mutex_unlock(&core->died_mutex);
            break;
        }
        usleep(1000);
    }
    return NULL;
}

void *death_monitor(void *arg)
{
    t_data *core = (t_data *)arg;
    t_philo *curr;
    uint64_t now;

    while (1)
    {
        // Always lock died_mutex first to ensure consistent lock order
        pthread_mutex_lock(&core->died_mutex);

        // If someone has died, exit the loop and end the monitor thread
        if (core->someone_died) {
            pthread_mutex_unlock(&core->died_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&core->died_mutex);

        // Iterate through the linked list of philosophers
        curr = core->philo_head;
        while (curr)  // Iterate through linked list
        {
            now = curr_time(core);

            // Lock the philosopher's meal mutex to check if they have died
            pthread_mutex_lock(&curr->meal_mutex);
            if (now - curr->last_eaten >= core->time_to_die)
            {
                pthread_mutex_unlock(&curr->meal_mutex);

                // Lock died_mutex to set the death flag
                pthread_mutex_lock(&core->died_mutex);
                if (!core->someone_died) {  // Only print once
                    core->someone_died = 1;
                    pthread_mutex_lock(&core->print_mutex);
                    printf("%lu %d died\n", now / 1000, curr->id);
                    pthread_mutex_unlock(&core->print_mutex);
                }
                pthread_mutex_unlock(&core->died_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&curr->meal_mutex);

            curr = curr->next; // Move to the next philosopher
        }

        usleep(500);  // Small delay to reduce CPU usage
    }
    return NULL;
}




