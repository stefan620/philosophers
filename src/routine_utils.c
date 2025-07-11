/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:48:14 by stefan            #+#    #+#             */
/*   Updated: 2025/07/09 21:26:11 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define LEFT_FORK   0
#define RIGHT_FORK  1
#define HAS_LEFT    2
#define HAS_RIGHT   3
#define IS_DEAD     4
#define STARTED     5
#define FIRST       6
#define SECOND      7

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
	return (1);
}

void	release_forks(t_philo *philo, int *v)
{
	if (v[HAS_LEFT])
		pthread_mutex_unlock(&philo->philosopher->forks[v[LEFT_FORK]]);
	if (v[HAS_RIGHT])
		pthread_mutex_unlock(&philo->philosopher->forks[v[RIGHT_FORK]]);
}
