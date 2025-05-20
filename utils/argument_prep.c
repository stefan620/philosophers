/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_prep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silic <silic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:58:04 by stefan            #+#    #+#             */
/*   Updated: 2025/05/13 17:44:21 by silic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int data_prep(t_philosopher *philosopher, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        return (write(2, ERR_MSG2, sizeof(ERR_MSG2)), 1);
    philosopher->number_of_philosophers = ft_atoi(argv[1]);
    if (philosopher->number_of_philosophers < 1)
        return (write(2, ERR_MSG3, sizeof(ERR_MSG3)), 1);
    philosopher->time_to_die = ft_atoi(argv[2]);
    if (philosopher->time_to_die < 1)
        return (write(2, ERR_MSG5, sizeof(ERR_MSG5)), 1);
    philosopher->time_to_eat = ft_atoi(argv[3]);
    if (philosopher->time_to_eat < 1)
        return (write(2, ERR_MSG6, sizeof(ERR_MSG6)), 1);
    philosopher->time_to_sleep = ft_atoi(argv[4]);
    if (philosopher->time_to_sleep < 1)
        return (write(2, ERR_MSG7, sizeof(ERR_MSG7)), 1);
    philosopher->number_of_times_each_philosopher_must_eat = -1;  // Default to -1 (infinite)
    if (argc == 6)
    {
        philosopher->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
        if (philosopher->number_of_times_each_philosopher_must_eat < 1)
            return (write(2, ERR_MSG4, sizeof(ERR_MSG4)), 1);
    }
    return (0);
}
int ft_atoi(const char *str)
{
    int sign = 1;
    int result = 0;

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (result * sign);
}

