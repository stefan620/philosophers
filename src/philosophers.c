/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:19:33 by stefan            #+#    #+#             */
/*   Updated: 2025/07/07 16:50:03 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_extend(t_philosopher philosopher);

int	main(int argc, char **argv)
{
	t_philosopher	philosopher;
	t_philo			*philo;
	t_control		control;
	int				i;

	i = 0;
	philosopher.dead = 0;
	if (data_prep(&philosopher, argc, argv))
		return (1);
	if (philosopher.num_of_philo == 1)
		return (philo_extend(philosopher), 0);
	philo = malloc(sizeof(t_philo) * philosopher.num_of_philo);
	if (!philo)
		return (1);
	philosopher.philo_array = philo;
	if (create_forks(&philosopher))
		return (free(philo), printf(ERR_FORKS), 1);
	if (create_philo(&philosopher, philo))
		return (free(philo),free(philosopher.forks) ,printf(ERR_PHILO), 1);
	if (init_control_thread(&philosopher, &control, philo))
		return (free(philo),free(philosopher.forks), printf(ERR_THREAD), 1);
	while (i < philosopher.num_of_philo)
		pthread_join(philo[i++].thread, NULL);
	pthread_join(control.ctrl_thread, NULL);
	return (cleanup(&philosopher), free(philo), free(philosopher.forks), 0);
}

static void	philo_extend(t_philosopher philosopher)
{
	printf(T_FORK, (int64_t)0, 1);
	usleep(philosopher.time_to_die * 1000);
	printf(DEAD_MSG, (int64_t)philosopher.time_to_die, 1);
}
