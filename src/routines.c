/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:23:43 by silic             #+#    #+#             */
/*   Updated: 2025/07/01 15:47:35 by stefan           ###   ########.fr       */
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
		if (philo_wait_for_start(philo))
			continue ;
		if (!philo_try_take_forks(philo, v))
		{
			usleep(100);
			continue ;
		}
		if (!philo_eat_and_check(philo, v))
			break ;
		philo_sleep_and_think(philo);
	}
	return (NULL);
}

static int	check_philo_death(t_philosopher *philosopher, t_philo *philos,
		int i)
{
	int64_t	time_since_last_meal;
	int64_t	t;

	t = philosopher->start_time;
	pthread_mutex_lock(&philos[i].meal_mutex);
	time_since_last_meal = get_time() - philos[i].last_meal;
	if (time_since_last_meal >= philosopher->time_to_die)
	{
		pthread_mutex_lock(&philosopher->dead_mutex);
		if (!philosopher->dead)
		{
			philosopher->dead = 1;
			printf(DEAD_MSG, get_time() - t, philos[i].id);
		}
		pthread_mutex_unlock(&philosopher->dead_mutex);
		pthread_mutex_unlock(&philos[i].meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos[i].meal_mutex);
	return (0);
}

static int	count_finished_eating(t_philosopher *philosopher, t_philo *philos)
{
	int	i;
	int	finished_eating_count;

	i = 0;
	finished_eating_count = 0;
	while (i < philosopher->num_of_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philosopher->number_of_times_each_eats != -1
			&& philos[i].meals_eaten >= philosopher->number_of_times_each_eats)
			finished_eating_count++;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	return (finished_eating_count);
}

static int	check_all_philos_finished(t_philosopher *philosopher,
		int finished_eating_count)
{
	if (philosopher->number_of_times_each_eats != -1
		&& finished_eating_count == philosopher->num_of_philo)
	{
		pthread_mutex_lock(&philosopher->dead_mutex);
		philosopher->dead = 1;
		pthread_mutex_unlock(&philosopher->dead_mutex);
		return (1);
	}
	return (0);
}

void	*control_routine(void *arg)
{
	int				i;
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
		while (i < philosopher->num_of_philo)
		{
			if (check_philo_death(philosopher, philos, i))
				return (NULL);
			i++;
		}
		finished_eating_count = count_finished_eating(philosopher, philos);
		if (check_all_philos_finished(philosopher, finished_eating_count))
			return (NULL);
		usleep(50);
	}
}
