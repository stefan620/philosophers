/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:03:29 by silic             #+#    #+#             */
/*   Updated: 2025/07/11 14:10:06 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_main_mutexes(t_philosopher *philosopher)
{
	if (pthread_mutex_init(&philosopher->start_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philosopher->print_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&philosopher->start_mutex), 1);
	if (pthread_mutex_lock(&philosopher->start_mutex) != 0)
		return (pthread_mutex_destroy(&philosopher->start_mutex),
			pthread_mutex_destroy(&philosopher->print_mutex), 1);
	philosopher->start = 0;
	philosopher->dead = 0;
	if (pthread_mutex_init(&philosopher->dead_mutex, NULL) != 0)
		return (pthread_mutex_unlock(&philosopher->start_mutex),
			pthread_mutex_destroy(&philosopher->start_mutex),
			pthread_mutex_destroy(&philosopher->print_mutex), 1);
	return (0);
}

int	create_all_philos(t_philosopher *philosopher, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philosopher->num_of_philo)
	{
		if (create_philo_extend(philosopher, philo, i))
		{
			thread_clean_with_mutexes(philo, i);
			pthread_mutex_destroy(&philosopher->dead_mutex);
			pthread_mutex_destroy(&philosopher->start_mutex);
			pthread_mutex_destroy(&philosopher->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_philo_timing(t_philosopher *philosopher)
{
	int	i;

	philosopher->start_time = get_time();
	i = 0;
	while (i < philosopher->num_of_philo)
	{
		philosopher->philo_array[i].last_meal = philosopher->start_time;
		i++;
	}
	philosopher->start = 1;
}
