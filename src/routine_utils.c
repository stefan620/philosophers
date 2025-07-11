/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:48:14 by stefan            #+#    #+#             */
/*   Updated: 2025/07/11 14:08:39 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_is_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->philosopher->dead_mutex);
	is_dead = philo->philosopher->dead;
	pthread_mutex_unlock(&philo->philosopher->dead_mutex);
	return (is_dead);
}

int	check_started(t_philo *philo)
{
	int	started;

	pthread_mutex_lock(&philo->philosopher->start_mutex);
	started = philo->philosopher->start;
	pthread_mutex_unlock(&philo->philosopher->start_mutex);
	return (started);
}

void	determine_fork_order(t_philo *philo, int *v)
{
	v[LEFT_FORK] = philo->id - 1;
	v[RIGHT_FORK] = philo->id % philo->philosopher->num_of_philo;
	v[HAS_LEFT] = 0;
	v[HAS_RIGHT] = 0;
	if ((philo->id - 1) % 2 == 0)
	{
		v[FIRST] = v[LEFT_FORK];
		v[SECOND] = v[RIGHT_FORK];
	}
	else
	{
		v[FIRST] = v[RIGHT_FORK];
		v[SECOND] = v[LEFT_FORK];
	}
}

int	take_forks(t_philo *philo, int *v)
{
	if (take_first_fork(philo, v) != 0)
		return (1);
	if (take_second_fork(philo, v) != 0)
		return (1);
	return (1);
}

void	release_forks(t_philo *philo, int *v)
{
	if (v[HAS_LEFT])
		pthread_mutex_unlock(&philo->philosopher->forks[v[LEFT_FORK]]);
	if (v[HAS_RIGHT])
		pthread_mutex_unlock(&philo->philosopher->forks[v[RIGHT_FORK]]);
}
