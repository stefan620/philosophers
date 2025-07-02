/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:28:23 by silic             #+#    #+#             */
/*   Updated: 2025/07/02 17:41:31 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philosopher *philosopher, int id)
{
	t_philo	*philo;

	philo = &philosopher->philo_array[id];
	pthread_mutex_lock(&philosopher->dead_mutex);
	if (philosopher->dead)
	{
		pthread_mutex_unlock(&philosopher->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philosopher->dead_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_lock(&philosopher->print_mutex);
	printf(EAT_MSG, philo->last_meal - philo->philosopher->start_time, id + 1);
	pthread_mutex_unlock(&philosopher->print_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_sleep(philosopher->time_to_eat, &philosopher->philo_array[id]);
}

void	sleep1(t_philosopher *philosopher, int id)
{
	pthread_mutex_lock(&philosopher->print_mutex);
	printf (SLEEP_MSG, get_time() - philosopher->start_time, id + 1);
	pthread_mutex_unlock(&philosopher->print_mutex);
	ft_sleep(philosopher->time_to_sleep, &philosopher->philo_array[id]);
}
