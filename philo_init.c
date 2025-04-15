#include "philosophers.h"

int	init_data(t_data *data)
{
	data->finished = 0;
	pthread_mutex_init(&data->finish_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->philos = NULL;
	data->forks = NULL;
	return (0);
}
