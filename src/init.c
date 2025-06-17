/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:26:18 by silic             #+#    #+#             */
/*   Updated: 2025/06/17 22:12:24 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_philo(t_philosopher *philosopher, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_init(&philosopher->start_mutex, NULL);
	pthread_mutex_lock(&philosopher->start_mutex);
	philosopher->start = 0;
	philosopher->dead = 0;
	pthread_mutex_init(&philosopher->dead_mutex, NULL);
	while (i < philosopher->number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].philosopher = philosopher;
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		philo[i].last_meal = get_time();
		if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]) != 0)
		{
			printf(ERR_PHILO);
			pthread_mutex_unlock(&philosopher->start_mutex);
			return (pthread_mutex_destroy(&philosopher->start_mutex), 1);
		}
		i++;
	}
	usleep(1000);
	philosopher->start = 1;
	return (pthread_mutex_unlock(&philosopher->start_mutex), 0);
}

int	create_forks(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	philosopher->forks = malloc(sizeof(pthread_mutex_t) * philosopher->number_of_philosophers);
	if (!philosopher->forks)
		return (1);
	while (i < philosopher->number_of_philosophers)
	{
		if (pthread_mutex_init(&philosopher->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	cleanup_mutexes(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	while (i < philosopher->number_of_philosophers)
	{
		pthread_mutex_destroy(&philosopher->philo_array[i].meal_mutex);
		pthread_mutex_destroy(&philosopher->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philosopher->dead_mutex);
	pthread_mutex_destroy(&philosopher->start_mutex);
}

int	init_control_thread(t_philosopher *philosopher, t_control *control, t_philo *philo_array)
{
	control->philosopher = philosopher;
	control->philo_array = philo_array;
	if (pthread_create(&control->ctrl_thread, NULL, control_routine, control) != 0)
	{
		printf(ERR_THREAD);
		return (1);
	}
	return (0);
}
