/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:28:48 by stefan            #+#    #+#             */
/*   Updated: 2025/07/07 17:29:12 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_philo_extend(t_philosopher *philosopher, t_philo *philo, int i)
{
	philo[i].id = i + 1;
	philo[i].philosopher = philosopher;
	if (pthread_mutex_init(&philo[i].meal_mutex, NULL) != 0)
	{
		printf(ERR_PHILO);
		pthread_mutex_unlock(&philosopher->start_mutex);
		return (1);
	}
	philo[i].last_meal = 0;
	philo[i].meals_eaten = 0;
	if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]) != 0)
	{
		printf(ERR_PHILO);
		pthread_mutex_destroy(&philo[i].meal_mutex);
		pthread_mutex_unlock(&philosopher->start_mutex);
		return (1);
	}
	return (0);
}
