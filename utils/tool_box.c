/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:16:40 by stefan            #+#    #+#             */
/*   Updated: 2025/07/07 17:29:12 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdint.h>

int64_t	get_time(void)
{
	struct timeval	time;
	int64_t			time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = ((int64_t)time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_in_ms);
}

void	ft_sleep(long duration_ms, t_philo *philo)
{
	long	start;

	start = get_time();
	while (!check_is_dead(philo))
	{
		if (get_time() - start >= duration_ms)
			break ;
		usleep(100);
	}
}

void	thread_clean(t_philo *philo, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_join(philo[j].thread, NULL);
		j++;
	}
}

void	thread_clean_with_mutexes(t_philo *philo, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_join(philo[j].thread, NULL);
		pthread_mutex_destroy(&philo[j].meal_mutex);
		j++;
	}
}
