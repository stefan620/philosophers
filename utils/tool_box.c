/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:16:40 by stefan            #+#    #+#             */
/*   Updated: 2025/05/04 22:17:43 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int get_time(void)
{
    struct timeval  time;
    int             time_in_ms;

    gettimeofday(&time, NULL);
    time_in_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (time_in_ms);
}