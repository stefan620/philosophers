/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:23:43 by silic             #+#    #+#             */
/*   Updated: 2025/06/22 13:14:53 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		v[8];

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	usleep(1000);
	while (1)
	{
		if (check_is_dead(philo))
			break ;
		if (!check_started(philo))
		{
			usleep(100);
			continue ;
		}
		determine_fork_order(philo, v);
		if (!take_forks(philo, v))
			break ;
		if (check_is_dead(philo))
		{
			release_forks(philo, v);
			break ;
		}
		eat(philo->philosopher, philo->id - 1);
		if (check_is_dead(philo))
		{
			release_forks(philo, v);
			break ;
		}
		release_forks(philo, v);
		sleep1(philo->philosopher, philo->id - 1);
		if (!check_is_dead(philo))
			printf(THINK_MSG, get_time(), philo->id);
	}
	return (NULL);
}

void	*control_routine(void *arg)
{
	int				i;
	int64_t			time_since_last_meal;
	t_control		*control;
	t_philosopher	*philosopher;
	t_philo			*philos;
	int				finished_eating_count;

	control = (t_control *)arg;
	philosopher = control->philosopher;
	philos = control->philo_array;
	while (1)
	{
		i = 0;
		finished_eating_count = 0;
		while (i < philosopher->number_of_philosophers)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			time_since_last_meal = get_time() - philos[i].last_meal;
			if (time_since_last_meal >= philosopher->time_to_die)
			{
				pthread_mutex_lock(&philosopher->dead_mutex);
				if (!philosopher->dead)
				{
					philosopher->dead = 1;
					printf(DEAD_MSG, get_time(), philos[i].id);
				}
				pthread_mutex_unlock(&philosopher->dead_mutex);
				pthread_mutex_unlock(&philos[i].meal_mutex);
				return (NULL);
			}
			if (philosopher->number_of_times_each_philo_must_eat != -1
				&& philos[i].meals_eaten >=
				philosopher->number_of_times_each_philo_must_eat)
				finished_eating_count++;
			pthread_mutex_unlock(&philos[i].meal_mutex);
			i++;
		}
		if (philosopher->number_of_times_each_philo_must_eat != -1
			&& finished_eating_count == philosopher->number_of_philosophers)
		{
			pthread_mutex_lock(&philosopher->dead_mutex);
			philosopher->dead = 1;
			pthread_mutex_unlock(&philosopher->dead_mutex);
			return (NULL);
		}
		usleep(50);
	}
}
