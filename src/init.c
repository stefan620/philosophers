/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:26:18 by silic             #+#    #+#             */
/*   Updated: 2025/06/30 16:49:34 by silic            ###   ########.fr       */
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
	pthread_mutex_init(&philosopher->waiter, NULL);
	while (i < philosopher->num_of_philo)
	{
		if (create_philo_extend(philosopher, philo, i))
			return (pthread_mutex_destroy(&philosopher->start_mutex), 1);
		i++;
	}
	philosopher->start_time = get_time();
	i = 0;
	while (i < philosopher->num_of_philo)
	{
		philo[i].last_meal = philosopher->start_time;
		i++;
	}
	philosopher->start = 1;
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
			return (1);
		i++;
	}
	return (0);
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
	pthread_mutex_destroy(&philosopher->waiter);
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
		return (1);
	}
	return (0);
}
