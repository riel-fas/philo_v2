// // #include "philosophers.h"

// // int philosophers(int ac, char **av)
// // {
// //     t_args input;

// //     if (input_pars(ac, av, &input) != 0)
// //         return (1);
// //     if (philo_act(&input) != 0)
// //         return (1);
// //     // If you have cleanup such as free_args(&input), add it here
// //     return (0);
// // }

// // int main(int ac, char **av)
// // {
// //     if (ac < 5 || ac > 6)
// //     {
// //         printf("⛔️INPUT SHOULD BE : ./philo x xx xxx xxxx [xxx]⛔️\n");
// //         printf("Where:\n");
// //         printf("x: number_of_philosophers and forks\n");
// //         printf("xx : time_to_die (in milliseconds)\n");
// //         printf("xxx: time_to_eat (in milliseconds)\n");
// //         printf("xxxx: time_to_sleep (in milliseconds)\n");
// //         printf("[xxx]: optional - number_of_times_each_philosopher_must_eat\n");
// //         return (1);
// //     }
// //     if (philosophers(ac, av) != 0)
// //         return (1);
// //     return (0);
// // }


// #include "philosophers.h"

// int philosophers(int ac, char **av)
// {
//     t_args input;
//     t_data data;

//     // 1. Parse input arguments
//     if (input_pars(ac, av, &input) != 0)
//         return (1);

//     // 2. Initialize your main data structure(s)
//     if (init_data(&data, &input) != 0)
//         return (1);

//     // 3. Initialize philosophers and forks
//     if (init_philos(&data) != 0)
//         return (1);
//     if (init_forks(&data) != 0)
//         return (1);

//     // 4. Launch threads (philosophers + monitors)
//     if (run_threads(&data) != 0)
//         return (1);

//     // 5. Join threads
//     if (join_threads(&data) != 0)
//         return (1);

//     // 6. Cleanup (free memory, destroy mutexes, etc.)
//     free_data(&data);

//     return (0);
// }

// int main(int ac, char **av)
// {
//     if (ac < 5 || ac > 6)
//     {
//         printf("⛔️INPUT SHOULD BE : ./philo x xx xxx xxxx [xxx]⛔️\n");
//         printf("Where:\n");
//         printf("x: number_of_philosophers and forks\n");
//         printf("xx : time_to_die (in milliseconds)\n");
//         printf("xxx: time_to_eat (in milliseconds)\n");
//         printf("xxxx: time_to_sleep (in milliseconds)\n");
//         printf("[xxx]: optional - number_of_times_each_philosopher_must_eat\n");
//         return (1);
//     }
//     if (philosophers(ac, av) != 0)
//         return (1);
//     return (0);
// }



#include "philosophers.h"


int main(int argc, char **argv)
{
    t_data data;
    pthread_t monitor_thread;

    if (parse_args(argc, argv, &data.args))
    {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }
    if (init_data(&data))
    {
        printf("Failed to initialize data\n");
        return (1);
    }
    if (init_philosophers_and_forks(&data))
    {
        printf("Failed to initialize philosophers or forks\n");
        return (1);
    }
	data.start_time = get_timestamp_ms();
    if (launch_philosopher_threads(&data))
    {
        printf("Failed to launch philosopher threads\n");
        cleanup(&data);
        return (1);
    }
    // Launch monitor
    pthread_create(&monitor_thread, NULL, death_monitor, &data);

    join_philosopher_threads(&data);

    pthread_join(monitor_thread, NULL);

    cleanup(&data);
    return 0;
}
