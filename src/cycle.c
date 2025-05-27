/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:28:23 by silic             #+#    #+#             */
/*   Updated: 2025/05/27 15:59:18 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void get_forks(t_philosopher *philosopher, int id)
{
    pthread_mutex_lock(&philosopher->forks[id]);
    printf(T_FORK,get_time() ,id + 1);
    pthread_mutex_lock(&philosopher->forks[(id + 1) % philosopher->number_of_philosophers]);
    printf(T_FORK,get_time(), (id + 1) % philosopher->number_of_philosophers + 1);
}

void put_forks(t_philosopher *philosopher, int id)
{
    pthread_mutex_unlock(&philosopher->forks[id]);
    printf(P_FORK, get_time(), id + 1);
    pthread_mutex_unlock(&philosopher->forks[(id + 1) % philosopher->number_of_philosophers]);
    printf(P_FORK, get_time(), (id + 1) % philosopher->number_of_philosophers + 1);}

void eat(t_philosopher *philosopher, int id)
{
    t_philo *philo = &philosopher->philo_array[id];
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->meal_mutex);
    printf(EAT_MSG,get_time() ,id + 1);
    usleep(philosopher->time_to_eat * 1000);
}
void sleep1(t_philosopher *philosopher, int id)
{
    printf(SLEEP_MSG,get_time() ,id + 1);
    usleep(philosopher->time_to_sleep * 1000);
}