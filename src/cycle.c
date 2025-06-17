/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:28:23 by silic             #+#    #+#             */
/*   Updated: 2025/06/17 21:20:15 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eat(t_philosopher *philosopher, int id)
{
    t_philo *philo = &philosopher->philo_array[id];
    int64_t start_time;
    int64_t end_time;

    start_time = get_time();
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = start_time;
    pthread_mutex_unlock(&philo->meal_mutex);
    pthread_mutex_lock(&philosopher->dead_mutex);
    if (philosopher->dead) {
        pthread_mutex_unlock(&philosopher->dead_mutex);
        return;
    }
    pthread_mutex_unlock(&philosopher->dead_mutex);
    printf(EAT_MSG, start_time, id + 1);
    usleep(philosopher->time_to_eat * 1000);
    end_time = get_time();
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = end_time;
    pthread_mutex_unlock(&philo->meal_mutex);
}

void sleep1(t_philosopher *philosopher, int id)
{
    printf(SLEEP_MSG,get_time() ,id + 1);
    usleep(philosopher->time_to_sleep * 1000);
}