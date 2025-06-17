/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:23:43 by silic             #+#    #+#             */
/*   Updated: 2025/06/02 20:29:34 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int left_fork, right_fork;
    int has_left = 0, has_right = 0;

    while (1)
    {
        pthread_mutex_lock(&philo->philosopher->dead_mutex);
        int is_dead = philo->philosopher->dead;
        pthread_mutex_unlock(&philo->philosopher->dead_mutex);
        if (is_dead)
            break;

        pthread_mutex_lock(&philo->philosopher->start_mutex);
        int started = philo->philosopher->start;
        pthread_mutex_unlock(&philo->philosopher->start_mutex);
        if (!started)
        {
            usleep(1000);
            continue;
        }

        // Fork order logic
        left_fork = philo->id - 1;
        right_fork = (philo->id) % philo->philosopher->number_of_philosophers;
        has_left = 0;
        has_right = 0;
        int first, second;
        if ((philo->id - 1) % 2 == 0) {
            first = left_fork;
            second = right_fork;
        } else {
            first = right_fork;
            second = left_fork;
        }
        pthread_mutex_lock(&philo->philosopher->forks[first]);
        has_left = (first == left_fork);
        has_right = (first == right_fork);
        printf(T_FORK, get_time(), philo->id);
        if (philo->philosopher->number_of_philosophers == 1)
        {
            usleep(philo->philosopher->time_to_die * 1000);
            pthread_mutex_unlock(&philo->philosopher->forks[first]);
            break;
        }
        pthread_mutex_lock(&philo->philosopher->forks[second]);
        has_left |= (second == left_fork);
        has_right |= (second == right_fork);
        printf(T_FORK, get_time(), philo->id);

        pthread_mutex_lock(&philo->philosopher->dead_mutex);
        is_dead = philo->philosopher->dead;
        pthread_mutex_unlock(&philo->philosopher->dead_mutex);
        if (is_dead)
        {
            if (has_left) pthread_mutex_unlock(&philo->philosopher->forks[left_fork]);
            if (has_right) pthread_mutex_unlock(&philo->philosopher->forks[right_fork]);
            break;
        }

        eat(philo->philosopher, philo->id - 1);

        pthread_mutex_lock(&philo->philosopher->dead_mutex);
        is_dead = philo->philosopher->dead;
        pthread_mutex_unlock(&philo->philosopher->dead_mutex);
        if (is_dead)
        {
            if (has_left) pthread_mutex_unlock(&philo->philosopher->forks[left_fork]);
            if (has_right) pthread_mutex_unlock(&philo->philosopher->forks[right_fork]);
            break;
        }

        if (has_left) pthread_mutex_unlock(&philo->philosopher->forks[left_fork]);
        if (has_right) pthread_mutex_unlock(&philo->philosopher->forks[right_fork]);
        sleep1(philo->philosopher, philo->id - 1);
        pthread_mutex_lock(&philo->philosopher->dead_mutex);
        is_dead = philo->philosopher->dead;
        pthread_mutex_unlock(&philo->philosopher->dead_mutex);
        if (!is_dead)
            printf(THINK_MSG, get_time(), philo->id);
    }
    return NULL;
}

void *control_routine(void *arg)
{
    t_control *control = (t_control *)arg;
    t_philosopher *philosopher = control->philosopher;
    t_philo *philos = control->philo_array;
    int i;
    int64_t current_time;
    int64_t time_since_last_meal;

    i = 0;
    while (1)
    {
        while (i < philosopher->number_of_philosophers)
        {
            pthread_mutex_lock(&philos[i].meal_mutex);
            current_time = get_time();
            time_since_last_meal = current_time - philos[i].last_meal;
            
            if (time_since_last_meal >= philosopher->time_to_die)
            {
                pthread_mutex_lock(&philosopher->dead_mutex);
                if (!philosopher->dead) {
                    philosopher->dead = 1;
                    printf(DEAD_MSG, current_time, philos[i].id);
                }
                pthread_mutex_unlock(&philosopher->dead_mutex);
                pthread_mutex_unlock(&philos[i].meal_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&philos[i].meal_mutex);
            i++;
        }
        i = 0;
        usleep(50);  // Check more frequently
    }
}
