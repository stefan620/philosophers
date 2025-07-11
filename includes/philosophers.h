/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:46:02 by stefan            #+#    #+#             */
/*   Updated: 2025/07/11 14:13:37 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h> // for int64_t
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// Error messages
# define ERR_MSG "Error: Invalid argument\n"
# define ERR_MSG2 "Error: Invalid number of arguments\n"
# define ERR_MSG3 "Error: Invalid number of philosophers\n"
# define ERR_MSG4 "Error: Invalid number of times each philosopher must eat\n"
# define ERR_MSG5 "Error: Invalid time to die\n"
# define ERR_MSG6 "Error: Invalid time to eat\n"
# define ERR_MSG7 "Error: Invalid time to sleep\n"
# define MEMORY_ERR "Error: Memory allocation failed\n"
# define CREATION "Philosopher %d is created\n"
# define ERR_FORKS "Error: Forks creation failed\n"
# define ERR_PHILO "Error: Philosopher creation failed\n"
# define ERR_THREAD "Error: Thread creation failed\n"
# define DEAD_MSG "%ld %d died\n"
# define EAT_MSG "%ld %d is eating\n"
# define SLEEP_MSG "%ld %d is sleeping\n"
# define THINK_MSG "%ld %d is thinking\n"
# define T_FORK "%ld %d has taken a fork\n"
# define P_FORK "%ld %d has put down a fork\n"
// Error messages

# define LEFT_FORK 0
# define RIGHT_FORK 1
# define HAS_LEFT 2
# define HAS_RIGHT 3
# define IS_DEAD 4
# define STARTED 5
# define FIRST 6
# define SECOND 7

struct	s_philosopher;

typedef struct s_philo
{
	int						id;
	pthread_t				thread;
	struct s_philosopher	*philosopher;
	pthread_mutex_t			meal_mutex;
	int						meals_eaten;
	int64_t					last_meal;
}							t_philo;

typedef struct s_control
{
	pthread_t				ctrl_thread;
	struct s_philosopher	*philosopher;
	t_philo					*philo_array;
}							t_control;

typedef struct s_philosopher
{
	t_philo					*philo_array;
	int						num_of_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						number_of_times_each_eats;
	int64_t					start_time;
	pthread_mutex_t			*forks;
	pthread_mutex_t			dead_mutex;
	pthread_mutex_t			start_mutex;
	pthread_mutex_t			print_mutex;
	int						start;
	int						dead;
}							t_philosopher;

int							data_prep(t_philosopher *philosopher, int argc,
								char **argv);
int							create_philo(t_philosopher *philosopher,
								t_philo *philo);
int							create_philo_extend(t_philosopher *philosopher,
								t_philo *philo, int i);
void						*philo_routine(void *arg);
int							ft_atoi(const char *str);
int64_t						get_time(void);
int							check_is_dead(t_philo *philo);
int							check_started(t_philo *philo);
void						determine_fork_order(t_philo *philo, int *v);
int							take_forks(t_philo *philo, int *v);
void						release_forks(t_philo *philo, int *v);

int							create_forks(t_philosopher *philosopher);
void						eat(t_philosopher *philosopher, int id);
void						sleep1(t_philosopher *philosopher, int id);
int							init_control_thread(t_philosopher *philosopher,
								t_control *control, t_philo *philo_array);
void						*control_routine(void *arg);
void						cleanup(t_philosopher *philosopher);
int							philo_try_take_forks(t_philo *philo, int *v);
int							philo_eat_and_check(t_philo *philo, int *v);
void						philo_sleep_and_think(t_philo *philo);
int							philo_wait_for_start(t_philo *philo);
void						ft_sleep(long duration_ms, t_philo *philo);
void						thread_clean(t_philo *philo, int i);
void						thread_clean_with_mutexes(t_philo *philo, int i);
void						clean_forks(t_philosopher *philosopher,
								int num_of_philo);
int							create_all_philos(t_philosopher *philosopher,
								t_philo *philo);
void						init_philo_timing(t_philosopher *philosopher);
int							init_main_mutexes(t_philosopher *philosopher);
int							take_second_fork(t_philo *philo, int *v);
int							take_first_fork(t_philo *philo, int *v);

#endif // PHILOSOPHERS_H
