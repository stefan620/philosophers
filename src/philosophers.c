#include "philosophers.h"

int main(int argc, char **argv)
{
    t_philosopher philosopher;
    t_philo *philo;
    t_control control;
    int i;

    i = 0;
    philosopher.dead = 0;    
    if (data_prep(&philosopher, argc, argv))
        return (1);
    philo = malloc(sizeof(t_philo) * philosopher.number_of_philosophers);
    if (!philo)
        return (1);
    philosopher.philo_array = philo;
    if (create_forks(&philosopher))
        return (free(philo),printf(ERR_fORKS), 1);
    if (create_philo(&philosopher, philo))
        return (free(philo),printf(ERR_PHILO), 1);
    if (init_control_thread(&philosopher, &control, philo))
        return (free(philo), printf(ERR_THREAD), 1);
    while (i < philosopher.number_of_philosophers)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    pthread_join(control.ctrl_thread, NULL);
    free(philo);
    free(philosopher.forks);
    return (0);
}








