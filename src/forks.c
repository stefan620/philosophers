/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:07:29 by silic             #+#    #+#             */
/*   Updated: 2025/07/11 14:10:01 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_first_fork(t_philo *philo, int *v)
{
	int	is_dead;

	usleep(1000);
	pthread_mutex_lock(&philo->philosopher->forks[v[FIRST]]);
	v[HAS_LEFT] = (v[FIRST] == v[LEFT_FORK]);
	v[HAS_RIGHT] = (v[FIRST] == v[RIGHT_FORK]);
	pthread_mutex_lock(&philo->philosopher->dead_mutex);
	is_dead = philo->philosopher->dead;
	if (is_dead)
	{
		pthread_mutex_unlock(&philo->philosopher->dead_mutex);
		pthread_mutex_unlock(&philo->philosopher->forks[v[FIRST]]);
		return (v[HAS_LEFT] = 0, v[HAS_RIGHT] = 0, 1);
	}
	pthread_mutex_lock(&philo->philosopher->print_mutex);
	printf(T_FORK, get_time() - philo->philosopher->start_time, philo->id);
	pthread_mutex_unlock(&philo->philosopher->print_mutex);
	pthread_mutex_unlock(&philo->philosopher->dead_mutex);
	return (0);
}

int	take_second_fork(t_philo *philo, int *v)
{
	int	is_dead;

	pthread_mutex_lock(&philo->philosopher->forks[v[SECOND]]);
	v[HAS_LEFT] |= (v[SECOND] == v[LEFT_FORK]);
	v[HAS_RIGHT] |= (v[SECOND] == v[RIGHT_FORK]);
	pthread_mutex_lock(&philo->philosopher->dead_mutex);
	is_dead = philo->philosopher->dead;
	if (is_dead)
	{
		pthread_mutex_unlock(&philo->philosopher->dead_mutex);
		pthread_mutex_unlock(&philo->philosopher->forks[v[FIRST]]);
		pthread_mutex_unlock(&philo->philosopher->forks[v[SECOND]]);
		return (v[HAS_LEFT] = 0, v[HAS_RIGHT] = 0, 1);
	}
	pthread_mutex_lock(&philo->philosopher->print_mutex);
	printf(T_FORK, get_time() - philo->philosopher->start_time, philo->id);
	pthread_mutex_unlock(&philo->philosopher->print_mutex);
	pthread_mutex_unlock(&philo->philosopher->dead_mutex);
	return (0);
}
