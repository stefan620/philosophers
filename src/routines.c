/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:23:43 by silic             #+#    #+#             */
/*   Updated: 2025/05/27 15:58:49 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (!philo->philosopher->dead)
    {
        if (philo->philosopher->start == 0)
        {
            usleep(1000);
            continue;
        }
        if (philo->philosopher->dead)
            break;
        get_forks(philo->philosopher, philo->id - 1);
        if (philo->philosopher->dead)
        {
            put_forks(philo->philosopher, philo->id - 1);
            break;
        }
        eat(philo->philosopher, philo->id - 1);
        put_forks(philo->philosopher, philo->id - 1);
        sleep1(philo->philosopher, philo->id - 1);
        printf(THINK_MSG,get_time(), philo->id);
    }
    printf(DEAD_MSG,get_time() ,philo->id);
    return NULL;
}

void *control_routine(void *arg)
{
    t_control *control = (t_control *)arg;
    t_philosopher *philosopher = control->philosopher;
    t_philo *philos = control->philo_array;
    int i;

    i = 0;
    while (1)
    {
        while (i < philosopher->number_of_philosophers)
        {
            pthread_mutex_lock(&philos[i].meal_mutex);
            if (get_time() - philos[i].last_meal >= philosopher->time_to_die)
            {
                printf(DEAD_MSG,get_time(),philos[i].id);
                philosopher->dead = 1;
                pthread_mutex_unlock(&philos[i].meal_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&philos[i].meal_mutex);
            i++;
        }
        usleep(1000);
    }
}
