#include "philosophers.h"

void	cleanup(t_data *data)
{
	int n;
	int i;

	if (!data)
		return;
	n = data->args.number_of_philosophers;
	if (data->forks)
	{
		for (i = 0; i < n; i++)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	pthread_mutex_destroy(&data->finish_mutex);
	pthread_mutex_destroy(&data->print_mutex); // <-- Add this!
}

long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	smart_sleep(long duration_ms, t_data *data)
{
	long start = get_timestamp_ms();
	while (!data->finished && (get_timestamp_ms() - start < duration_ms))
		usleep(1000); // sleep 1ms, check finished flag frequently
}

int	safe_print(t_philo *philo, const char *msg)
{
	int	stop;
	long	now;
	long	elapsed;

	pthread_mutex_lock(&philo->data->finish_mutex);
	stop = philo->data->finished;
	pthread_mutex_unlock(&philo->data->finish_mutex);
	if (stop)
		return (1);
	now = get_timestamp_ms();
	elapsed = now - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", elapsed, philo->id, msg); // Print elapsed time!
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}
