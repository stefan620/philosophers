#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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


typedef struct s_philosopher
{
    int           time_to_die;
    int           time_to_eat;
    int           time_to_sleep;
    int           number_of_philosophers;
    int           number_of_times_each_philosopher_must_eat;
    int           *id;
    pthread_t    *threads;
    pthread_mutex_t *forks;
} t_philosopher;

// Function prototypes utils
int data_prep(t_philosopher *philosopher, int argc, char **argv);
int ft_atoi(const char *str);
int get_time(void);
void eat(t_philosopher *forks, int i);
void get_forks(t_philosopher *forks, int i);

// Function prototypes src
int create_threads(t_philosopher *philosopher);
void *philosopher_routine(void *arg);
int  create_mutexes(t_philosopher *philosopher);
int real_routine(t_philosopher *philosopher);

#endif // PHILOSOPHERS_H