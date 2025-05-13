/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:46:59 by stefan            #+#    #+#             */
/*   Updated: 2025/05/13 17:48:46 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    t_philosopher philosopher;
    
    if (data_prep(&philosopher, argc, argv))
        return (1);
    if (create_threads(&philosopher))
        return (1);
    if (create_mutexes(&philosopher))
        return (1);
    if (real_routine(&philosopher))
        return (1);    
}
int create_threads(t_philosopher *philosopher)
{
    int i;
    
    philosopher->id = malloc(sizeof(int) * philosopher->number_of_philosophers);
    if (!philosopher->id)
        return (write(2, MEMORY_ERR, sizeof(MEMORY_ERR)), 1);
    philosopher->threads = malloc(sizeof(pthread_t) * philosopher->number_of_philosophers);
    if (!philosopher->threads)
    {
        free(philosopher->id);
        return (write(2, MEMORY_ERR, sizeof(MEMORY_ERR)), 1);
    }
    for (i = 0; i < philosopher->number_of_philosophers; i++)
    {
        philosopher->id[i] = i + 1;
        if (pthread_create(&philosopher->threads[i], NULL, philosopher_routine, &philosopher->id[i]))
        {
            free(philosopher->id);
            free(philosopher->threads);
            return (write(2, MEMORY_ERR, sizeof(MEMORY_ERR)), 1);
        }
        printf(CREATION, philosopher->id[i]);
    }
    return (0);
}
int  create_mutexes(t_philosopher *philosopher)
{
    int i;

    i = 0;
    philosopher->forks = malloc(sizeof(pthread_mutex_t) * philosopher->number_of_philosophers);
    while (i < philosopher->number_of_philosophers)
    {
        if (pthread_mutex_init(&philosopher->forks[i], NULL))
        {
            free(philosopher->forks);// add mutex destruction if failed later
            return (write(2, MEMORY_ERR, sizeof(MEMORY_ERR)), 1);
        }
        printf("Fork %d created\n", i + 1);
        i++;
    }
    return (0);
}
void  *philosopher_routine(void *arg)
{
    (void)arg;
    return (NULL);
}

int real_routine(t_philosopher *philosopher)
{
    int i;
    int num_eats;

    i = 0;
    num_eats = 0;
    while (1)
    {
        if (i >= philosopher->number_of_philosophers)
            i = 0;
        get_forks(philosopher, i);
        eat(philosopher, i);
        i++;
        num_eats++;
        // if (num_eats >= philosopher->number_of_times_each_philosopher_must_eat * philosopher->number_of_philosophers)
        // {
        //     printf("Philosopher %d has eaten %d times\n", i + 1, num_eats);
        //     break;
        // }
    }
    return (0);
}
void eat(t_philosopher *philosopher, int i)
{
    printf("Philosopher %d is eating\n", i + 1);
    usleep(philosopher->time_to_eat * 100000);
    pthread_mutex_unlock(&philosopher->forks[i]);
    pthread_mutex_unlock(&philosopher->forks[i + 1]);
    printf("Philosopher %d has put down forks\n", i + 1);
    printf("Philosopher %d is sleeping\n", i + 1);
    usleep(philosopher->time_to_sleep * 100000);
}
void get_forks(t_philosopher *philosopher, int i)
{
    printf("Philosopher %d is getting forks\n", i + 1);
    usleep(100);
    pthread_mutex_lock(&philosopher->forks[i]);
    pthread_mutex_lock(&philosopher->forks[i+1]);
    printf("Philosopher %d has taken forks%d %d\n", i + 1, i, i+1);
    usleep(100);
}
