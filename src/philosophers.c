/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:40:12 by silic             #+#    #+#             */
/*   Updated: 2025/05/21 22:45:15 by stefan           ###   ########.fr       */
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
int init_control_thread(t_philosopher *philosopher, t_control *control);
void *control_routine(void *arg);

int main(int argc, char **argv)
{
    t_philosopher philosopher;
    t_philo *philos;
    t_control control;

    philosopher.dead = 0;    
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
    if (init_control_thread(&philosopher, &control))
    {
        free(philos);
        printf("Error creating control thread\n");
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
        pthread_mutex_init(&philosopher[i].meal_mutex, NULL);
        if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]) != 0)
        {
            perror("Failed to create thread");
            return (1);
        }
        i++;
    }
    usleep(1000);
    philosopher->start = 1;
    return (0);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    printf(CREATION, philo->id);
    while (!philo->philosopher->dead)
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
    printf("Philosopher %d is dead\n", philo->id);
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
    // Lock before updating the last meal time
    pthread_mutex_lock(&philosopher->meal_mutex);
    philosopher->last_meal = get_time();
    printf("Philosopher %d is eating\n", get_time());
    pthread_mutex_unlock(&philosopher->meal_mutex);
    printf("Philosopher %d is eating\n", id + 1);
    usleep(philosopher->time_to_eat * 1000); // Multiply by 1000 (not 10000!) to convert ms to µs
}
void sleep1(t_philosopher *philosopher, int id)
{
    printf("Philosopher %d is sleeping\n", id + 1);
    usleep(philosopher->time_to_sleep * 1000);
}
int init_control_thread(t_philosopher *philosopher, t_control *control)
{
    philosopher->start = 0;
    control->philosopher = philosopher;
    if (pthread_create(&control->ctrl_thread, NULL, control_routine, control) != 0)
    {
        perror("Failed to create control thread");
        return (1);
    }
    return (0);
}

void *control_routine(void *arg)
{
    t_control *control = (t_control *)arg;
    control->philosopher->dead = 0;
    while (1)
    {
        pthread_mutex_lock(&control->philosopher->meal_mutex);
        printf("%ld %ld\n", control->philosopher->last_meal, control->philosopher->time_to_die);
        pthread_mutex_unlock(&control->philosopher->meal_mutex);
        printf("%ld\n", get_time());
        sleep(100);
        if (get_time() - control->philosopher->last_meal >= control->philosopher->time_to_die)
        {
            control->philosopher->dead = 1;
        }
        usleep(100);
        
    }
    return (NULL);
}
