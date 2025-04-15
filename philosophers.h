#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_args
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat; // -1 if unlimited/not set
}   t_args;

struct s_philo;

typedef struct s_data
{
    t_args              args;
    struct s_philo      *philos;
    pthread_mutex_t     *forks;
    int                 finished;
    pthread_mutex_t     finish_mutex;
    pthread_mutex_t     print_mutex;
	long                start_time;
}   t_data;

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long            last_meal_time;
    t_data          *data;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}   t_philo;

// Argument/data initialization
int parse_args(int argc, char **argv, t_args *args);
int init_data(t_data *data);
int init_philosophers_and_forks(t_data *data);

// Thread and routine
int launch_philosopher_threads(t_data *data);
int join_philosopher_threads(t_data *data);
void *philo_routine(void *arg);
void philo_eat(t_philo *philo);
void philo_sleep(t_philo *philo);
void philo_think(t_philo *philo);

// Monitor
void *death_monitor(void *arg);

// Cleanup
void cleanup(t_data *data);

// Time
long get_timestamp_ms(void);
void smart_sleep(long duration_ms, t_data *data);

// Printing
int safe_print(t_philo *philo, const char *msg);

#endif // PHILOSOPHERS_H
