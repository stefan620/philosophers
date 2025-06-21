/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:28:23 by silic             #+#    #+#             */
/*   Updated: 2025/06/21 15:48:10 by stefan           ###   ########.fr       */
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
	printf(EAT_MSG, philo->last_meal, id + 1);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philosopher->time_to_eat * 1000);
}


void	sleep1(t_philosopher *philosopher, int id)
{
	printf (SLEEP_MSG, get_time(), id + 1);
	usleep (philosopher->time_to_sleep * 1000);
}
