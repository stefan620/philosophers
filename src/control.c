/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:37:28 by silic             #+#    #+#             */
/*   Updated: 2025/05/15 17:51:00 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int create_control_thread(t_philosopher *philosopher)
{
    philosopher->control = malloc(sizeof(pthread_t));
    if (!philosopher->control)
    {
        free(philosopher->forks);
        return (write(2, MEMORY_ERR, sizeof(MEMORY_ERR)), 1);
    }
    if (pthread_create(philosopher->control, NULL, control_routine, philosopher))
    {
        free(philosopher->forks);
        return (write(2, MEMORY_ERR, sizeof(MEMORY_ERR)), 1);
    }
    return (0);
}
void *control_routine(void *arg)
{
    t_philosopher *philosopher;
    int i;

    i = 0;
    philosopher = (t_philosopher *)arg;
    while (1)
    {
        while(i < philosopher->number_of_philosophers)
        {
            if (get_time() - *philosopher->last_meal > philosopher->time_to_die)
            {
                printf("Philosopher %d has died\n", i + 1);
                philosopher->status = 1;
                return (NULL);
            }
            i++;
        }
    }
    return (NULL);
}