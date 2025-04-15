#include "philosophers.h"

void	*death_monitor(void *arg)
{
	t_data *data = (t_data *)arg;
	int i, n;
	long now;

	n = data->args.number_of_philosophers;
	while (1)
	{
		usleep(1000); // check every millisecond

		int full_count = 0;
		for (i = 0; i < n; i++)
		{
			pthread_mutex_lock(&data->finish_mutex);
			if (data->finished)
			{
				pthread_mutex_unlock(&data->finish_mutex);
				return NULL;
			}
			now = get_timestamp_ms();
			if (now - data->philos[i].last_meal_time > data->args.time_to_die)
			{
				long elapsed = now - data->start_time;
				data->finished = 1;
				pthread_mutex_lock(&data->print_mutex);
				printf("%ld %d died\n", elapsed, data->philos[i].id); // Use elapsed time for death
				pthread_mutex_unlock(&data->print_mutex);
				pthread_mutex_unlock(&data->finish_mutex);
				return NULL;
			}
			if (data->args.number_of_times_each_philosopher_must_eat > 0 &&
				data->philos[i].meals_eaten >= data->args.number_of_times_each_philosopher_must_eat)
				full_count++;
			pthread_mutex_unlock(&data->finish_mutex);
		}
		if (data->args.number_of_times_each_philosopher_must_eat > 0 && full_count == n)
		{
			pthread_mutex_lock(&data->finish_mutex);
			data->finished = 1;
			pthread_mutex_unlock(&data->finish_mutex);
			return NULL;
		}
	}
	return NULL;
}
