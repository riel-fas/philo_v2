#include "philosophers.h"

void philo_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    if (safe_print(philo, "has taken a fork")) {
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    pthread_mutex_lock(philo->right_fork);
    if (safe_print(philo, "has taken a fork")) {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    if (safe_print(philo, "is eating")) {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }

    // Update the last meal time
    pthread_mutex_lock(&philo->data->finish_mutex);
    philo->last_meal_time = get_timestamp_ms();
    pthread_mutex_unlock(&philo->data->finish_mutex);

    smart_sleep(philo->data->args.time_to_eat, philo->data);

    philo->meals_eaten++;

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

// void	philo_eat(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->left_fork);
// 	if (safe_print(philo, "has taken a fork")) {
// 		pthread_mutex_unlock(philo->left_fork);
// 		return;
// 	}
// 	pthread_mutex_lock(philo->right_fork);
// 	if (safe_print(philo, "has taken a fork")) {
// 		pthread_mutex_unlock(philo->right_fork);
// 		pthread_mutex_unlock(philo->left_fork);
// 		return;
// 	}
// 	if (safe_print(philo, "is eating")) {
// 		pthread_mutex_unlock(philo->right_fork);
// 		pthread_mutex_unlock(philo->left_fork);
// 		return;
// 	}
// 	philo->last_meal_time = get_timestamp_ms();
// 	smart_sleep(philo->data->args.time_to_eat, philo->data);

// 	philo->meals_eaten++;

// 	pthread_mutex_unlock(philo->right_fork);
// 	pthread_mutex_unlock(philo->left_fork);
// }

void	philo_sleep(t_philo *philo)
{
	if (safe_print(philo, "is sleeping"))
		return;
	smart_sleep(philo->data->args.time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	safe_print(philo, "is thinking");
}

// void	*philo_routine(void *arg)
// {
// 	t_philo *philo = (t_philo *)arg;
// 	int max_meals = philo->data->args.number_of_times_each_philosopher_must_eat;

// 	philo->last_meal_time = get_timestamp_ms();

// 	// Stagger even philosophers to prevent starvation
// 	if (philo->id % 2 == 0)
// 		usleep(1000 * (philo->data->args.time_to_eat / 2));

// 	while (max_meals == -1 || philo->meals_eaten < max_meals)
// 	{
// 		pthread_mutex_lock(&philo->data->finish_mutex);
// 		if (philo->data->finished)
// 		{
// 			pthread_mutex_unlock(&philo->data->finish_mutex);
// 			break;
// 		}
// 		pthread_mutex_unlock(&philo->data->finish_mutex);

// 		philo_eat(philo);
// 		philo_sleep(philo);
// 		philo_think(philo);
// 	}
// 	return (NULL);
// }

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int max_meals = philo->data->args.number_of_times_each_philosopher_must_eat;

    philo->last_meal_time = get_timestamp_ms();

    // Initial stagger for even philosophers
    if (philo->id % 2 == 0)
        usleep(1000 * (philo->data->args.time_to_eat / 2));

    while (max_meals == -1 || philo->meals_eaten < max_meals)
    {
        pthread_mutex_lock(&philo->data->finish_mutex);
        if (philo->data->finished)
        {
            pthread_mutex_unlock(&philo->data->finish_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->finish_mutex);

        // Add stagger for even philosophers before every eating attempt
        if (philo->id % 2 == 0)
            usleep(1000); // 1ms delay for even philosophers

        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}
