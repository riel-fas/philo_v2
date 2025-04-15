#include "philosophers.h"

int	launch_philosopher_threads(t_data *data)
{
	int i;
	int n = data->args.number_of_philosophers;

	for (i = 0; i < n; i++)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d\n", i + 1);
			return (1);
		}
	}
	return (0);
}

int	join_philosopher_threads(t_data *data)
{
	int i;
	int n = data->args.number_of_philosophers;

	for (i = 0; i < n; i++)
		pthread_join(data->philos[i].thread, NULL);
	return (0);
}
