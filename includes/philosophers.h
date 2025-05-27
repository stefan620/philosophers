#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // for int64_t

// Error messages
#define ERR_MSG "Error: Invalid argument\n"
#define ERR_MSG2 "Error: Invalid number of arguments\n"
#define ERR_MSG3 "Error: Invalid number of philosophers\n"
#define ERR_MSG4 "Error: Invalid number of times each philosopher must eat\n"
#define ERR_MSG5 "Error: Invalid time to die\n"
#define ERR_MSG6 "Error: Invalid time to eat\n"
#define ERR_MSG7 "Error: Invalid time to sleep\n"
#define MEMORY_ERR "Error: Memory allocation failed\n"
#define CREATION "Philosopher %d is created\n"
#define ERR_fORKS "Error: Forks creation failed\n"
#define ERR_PHILO "Error: Philosopher creation failed\n"
#define ERR_THREAD "Error: Thread creation failed\n"
#define DEAD_MSG "%ld %d is dead\n"
#define EAT_MSG "%ld %d is eating\n"
#define SLEEP_MSG "%ld %d is sleeping\n"
#define THINK_MSG "%ld %d is thinking\n"
#define T_FORK "%ld %d has taken fork\n"
#define P_FORK "%ld %d has put down fork\n"
//Error messages

struct s_philosopher;

typedef struct s_philo {
    int id;
    pthread_t thread;
    struct s_philosopher *philosopher;
    pthread_mutex_t meal_mutex;
    int64_t last_meal;
} t_philo;

typedef struct s_control {
    pthread_t ctrl_thread;
    struct s_philosopher *philosopher;
    t_philo *philo_array;
} t_control;

typedef struct s_philosopher {
    t_philo *philo_array;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    pthread_mutex_t *forks;
    int start;
    int dead;
} t_philosopher;

// Function declarations
int data_prep(t_philosopher *philosopher, int argc, char **argv);
int create_philo(t_philosopher *philosopher, t_philo *philo);
void *philo_routine(void *arg);
int ft_atoi(const char *str);
int64_t get_time(void);

// Internal helpers declared in philosophers.c
int create_forks(t_philosopher *philosopher);
void get_forks(t_philosopher *philosopher, int id);
void put_forks(t_philosopher *philosopher, int id);
void eat(t_philosopher *philosopher, int id);
void sleep1(t_philosopher *philosopher, int id);
int init_control_thread(t_philosopher *philosopher, t_control *control, t_philo *philo_array);
void *control_routine(void *arg);

#endif // PHILOSOPHERS_H
