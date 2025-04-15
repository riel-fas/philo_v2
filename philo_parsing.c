#include "philosophers.h"

int	parse_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
		return (1);
	args->number_of_philosophers = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		args->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	else
		args->number_of_times_each_philosopher_must_eat = -1;
	if (args->number_of_philosophers <= 0 || args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0)
		return (1);
	return (0);
}
