/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:40:12 by silic             #+#    #+#             */
/*   Updated: 2025/05/20 17:41:27 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int create_philo(t_philosopher *philosopher, t_philo *philos);
void *philo_routine(void *arg);

int main(int argc, char **argv)
{
    t_philosopher philosopher;
    t_philo *philos;

    if (data_prep(&philosopher, argc, argv))
        return (1);

    philos = malloc(sizeof(t_philo) * philosopher.number_of_philosophers);
    if (!philos)
        return (1);

    if (create_philo(&philosopher, philos))
    {
        free(philos);
        return (1);
    }
    free(philos);
    return (0);
}

int create_philo(t_philosopher *philosopher, t_philo *philos)
{
    int i = 0;

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
    return (0);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    printf("check\n");
    printf(CREATION, philo->id);
    return (NULL);
}
