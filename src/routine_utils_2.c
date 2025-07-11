/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:04:32 by silic             #+#    #+#             */
/*   Updated: 2025/07/11 14:26:14 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_try_take_forks(t_philo *philo, int *v)
{
	determine_fork_order(philo, v);
	if (!take_forks(philo, v))
		return (0);
	if (check_is_dead(philo))
	{
		release_forks(philo, v);
		return (0);
	}
	return (1);
}

int	philo_eat_and_check(t_philo *philo, int *v)
{
	eat(philo->philosopher, philo->id - 1);
	if (check_is_dead(philo))
	{
		release_forks(philo, v);
		return (0);
	}
	release_forks(philo, v);
	return (1);
}

void	philo_sleep_and_think(t_philo *philo)
{
	int64_t	start_time;
	int		is_dead;

	start_time = philo->philosopher->start_time;
	sleep1(philo->philosopher, philo->id - 1);
	pthread_mutex_lock(&philo->philosopher->dead_mutex);
	is_dead = philo->philosopher->dead;
	if (!is_dead)
	{
		pthread_mutex_lock(&philo->philosopher->print_mutex);
		printf(THINK_MSG, get_time() - start_time, philo->id);
		pthread_mutex_unlock(&philo->philosopher->print_mutex);
	}
	pthread_mutex_unlock(&philo->philosopher->dead_mutex);
}

int	philo_wait_for_start(t_philo *philo)
{
	if (check_is_dead(philo))
		return (0);
	if (!check_started(philo))
	{
		usleep(100);
		return (1);
	}
	return (0);
}
