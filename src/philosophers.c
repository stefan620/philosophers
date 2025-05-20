/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:40:12 by silic             #+#    #+#             */
/*   Updated: 2025/05/20 18:09:23 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int create_philo(t_philosopher *philosopher, t_philo *philos);
void *philo_routine(void *arg);
int create_forks(t_philosopher *philosopher);
void get_forks(t_philosopher *philosopher, int id);
void put_forks(t_philosopher *philosopher, int id);
void eat(t_philosopher *philosopher, int id);
void sleep1(t_philosopher *philosopher, int id);

int main(int argc, char **argv)
{
    t_philosopher philosopher;
    t_philo *philos;

    if (data_prep(&philosopher, argc, argv))
        return (1);

    philos = malloc(sizeof(t_philo) * philosopher.number_of_philosophers);
    if (!philos)
        return (1);
    if (create_forks(&philosopher))
    {
        free(philos);
        printf("Error creating forks\n");
        return (1);
    }

    if (create_philo(&philosopher, philos))
    {
        free(philos);
        printf("Error creating philosopher threads\n");
        return (1);
    }
    for (int i = 0; i < philosopher.number_of_philosophers; i++)
    {
        pthread_join(philos[i].thread, NULL);
    }

    free(philos);
    free(philosopher.forks);
    return (0);
}

int create_philo(t_philosopher *philosopher, t_philo *philos)
{
    int i = 0;

    philosopher->start = 0;
    while (i < philosopher->number_of_philosophers)
    {
        philos[i].id = i + 1;
        philos[i].philosopher = philosopher; 

        if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]) != 0)
        {
            perror("Failed to create thread");
            return (1);
        }
        i++;
    }
    philosopher->start = 1;
    return (0);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    printf(CREATION, philo->id);
    while (1)
    {
        while (1)
        {
            if (philo->philosopher->start == 1)
                break;
        }
        get_forks(philo->philosopher, philo->id - 1);
        eat(philo->philosopher, philo->id - 1);
        put_forks(philo->philosopher, philo->id - 1);
        sleep1(philo->philosopher, philo->id - 1);
        printf("Philosopher %d is thinking\n", philo->id);
    }
    return (NULL);
}
int create_forks(t_philosopher *philosopher)
{
    int i;

    philosopher->forks = malloc(sizeof(pthread_mutex_t) * philosopher->number_of_philosophers);
    if (!philosopher->forks)
        return (1);
    for (i = 0; i < philosopher->number_of_philosophers; i++)
    {
        if (pthread_mutex_init(&philosopher->forks[i], NULL) != 0)
        {
            free(philosopher->forks);
            return (1);
        }
    }
    return (0);
}
void get_forks(t_philosopher *philosopher, int id)
{
    pthread_mutex_lock(&philosopher->forks[id]);
    pthread_mutex_lock(&philosopher->forks[(id + 1) % philosopher->number_of_philosophers]);
    printf("Philosopher %d has taken forks %d and %d\n", id + 1, id + 1, (id + 1) % philosopher->number_of_philosophers + 1);
}   
void put_forks(t_philosopher *philosopher, int id)
{
    pthread_mutex_unlock(&philosopher->forks[id]);
    pthread_mutex_unlock(&philosopher->forks[(id + 1) % philosopher->number_of_philosophers]);
    printf("Philosopher %d has put down forks %d and %d\n", id + 1, id + 1, (id + 1) % philosopher->number_of_philosophers + 1);
}
void eat(t_philosopher *philosopher, int id)
{
    printf("Philosopher %d is eating\n", id + 1);
    usleep(philosopher->time_to_eat * 10000);
}
void sleep1(t_philosopher *philosopher, int id)
{
    printf("Philosopher %d is sleeping\n", id + 1);
    usleep(philosopher->time_to_sleep * 10000);
}
