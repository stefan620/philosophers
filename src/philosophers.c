/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:46:59 by stefan            #+#    #+#             */
/*   Updated: 2025/05/04 19:03:08 by stefan           ###   ########.fr       */
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
}
int create_threads(t_philosopher *philosopher)
{
    pthread_t *threads;
    int i;

    i = 0;
    threads = malloc(sizeof(pthread_t) * philosopher->number_of_philosophers);
    if (!threads)
        return (write(2, MEMORY_ERR, 32), 1);
    philosopher->threads = threads;
    philosopher->id = malloc(sizeof(int) * philosopher->number_of_philosophers);
    if (!philosopher->id)
    {
        free(threads);
        return (write(2, MEMORY_ERR, 32), 1);
    }
    while (i < philosopher->number_of_philosophers)
    {
        philosopher->id[i] = i + 1;
        i++;
    }
    i = 0;
    while (i < philosopher->number_of_philosophers)
    {
        if (pthread_create(&threads[i], NULL, philosopher_routine, &philosopher->id[i]))
        {
            while(--i != -1)
                pthread_detach(threads[i]);
            return (write(2, MEMORY_ERR, 32), 1);
        }
        pthread_join(threads[i], NULL);
        i++;
    }
    return (0);
}
void  *philosopher_routine(void *arg)
{
    int *id;
    id = (int *)arg;
    printf(CREATION, *id);
    return (0);
}