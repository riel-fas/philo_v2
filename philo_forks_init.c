#include "philosophers.h"

int	init_philosophers_and_forks(t_data *data)
{
	int	i;
	int	n;

	n = data->args.number_of_philosophers;
	data->philos = malloc(sizeof(t_philo) * n);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!data->forks)
	{
		free(data->philos);
		return (1);
	}
	for (i = 0; i < n; i++)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
	}
	for (i = 0; i < n; i++)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		// Odd: left then right, Even: right then left
		if (data->philos[i].id % 2 == 0)
		{
			data->philos[i].left_fork = &data->forks[i];
			data->philos[i].right_fork = &data->forks[(i + 1) % n];
			// swap order for even
			pthread_mutex_t *tmp = data->philos[i].left_fork;
			data->philos[i].left_fork = data->philos[i].right_fork;
			data->philos[i].right_fork = tmp;
		}
		else
		{
			data->philos[i].left_fork = &data->forks[i];
			data->philos[i].right_fork = &data->forks[(i + 1) % n];
		}
	}
	return (0);
}
