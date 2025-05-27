/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:26:18 by silic             #+#    #+#             */
/*   Updated: 2025/05/27 16:05:40 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int create_philo(t_philosopher *philosopher, t_philo *philo)
{
    philosopher->start = 0;
    for (int i = 0; i < philosopher->number_of_philosophers; i++)
    {
        philo[i].id = i + 1;
        philo[i].philosopher = philosopher; 
        pthread_mutex_init(&philo[i].meal_mutex, NULL);
        philo[i].last_meal = get_time();
        if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]) != 0)
        {
            printf(ERR_PHILO);
            return (1);
        }
    }
    usleep(1000);
    philosopher->start = 1;
    return (0);
}

int create_forks(t_philosopher *philosopher)
{
    philosopher->forks = malloc(sizeof(pthread_mutex_t) * philosopher->number_of_philosophers);
    if (!philosopher->forks)
        return 1;

    for (int i = 0; i < philosopher->number_of_philosophers; i++)
        if (pthread_mutex_init(&philosopher->forks[i], NULL) != 0)
            return 1;

    return 0;
}
int init_control_thread(t_philosopher *philosopher, t_control *control, t_philo *philo_array)
{
    control->philosopher = philosopher;
    control->philo_array = philo_array;

    if (pthread_create(&control->ctrl_thread, NULL, control_routine, control) != 0)
    {
        printf(ERR_THREAD);
        return 1;
    }
    return 0;
}