/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:26:18 by silic             #+#    #+#             */
/*   Updated: 2025/07/11 14:06:09 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_philo(t_philosopher *philosopher, t_philo *philo)
{
	if (init_main_mutexes(philosopher) != 0)
		return (1);
	if (create_all_philos(philosopher, philo) != 0)
		return (1);
	init_philo_timing(philosopher);
	return (pthread_mutex_unlock(&philosopher->start_mutex), 0);
}

int	create_forks(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	philosopher->forks = malloc(sizeof(pthread_mutex_t)
			* philosopher->num_of_philo);
	if (!philosopher->forks)
		return (1);
	while (i < philosopher->num_of_philo)
	{
		if (pthread_mutex_init(&philosopher->forks[i], NULL) != 0)
		{
			clean_forks(philosopher, i);
			free(philosopher->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

void	clean_forks(t_philosopher *philosopher, int num_of_philo)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{
		pthread_mutex_destroy(&philosopher->forks[i]);
		i++;
	}
}

void	cleanup(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	while (i < philosopher->num_of_philo)
	{
		pthread_mutex_destroy(&philosopher->philo_array[i].meal_mutex);
		pthread_mutex_destroy(&philosopher->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philosopher->dead_mutex);
	pthread_mutex_destroy(&philosopher->start_mutex);
	pthread_mutex_destroy(&philosopher->print_mutex);
}

int	init_control_thread(t_philosopher *philosopher, t_control *control,
		t_philo *philo_array)
{
	control->philosopher = philosopher;
	control->philo_array = philo_array;
	if (pthread_create(&control->ctrl_thread, NULL, control_routine,
			control) != 0)
	{
		printf(ERR_THREAD);
		thread_clean(philo_array, philosopher->num_of_philo);
		return (1);
	}
	return (0);
}
