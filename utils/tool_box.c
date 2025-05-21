/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:16:40 by stefan            #+#    #+#             */
/*   Updated: 2025/05/21 22:46:20 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdint.h>

int64_t get_time(void)
{
    struct timeval time;
    int64_t time_in_ms;

    gettimeofday(&time, NULL);
    time_in_ms = ((int64_t)time.tv_sec * 1000) + (time.tv_usec / 1000);
    return time_in_ms;
}