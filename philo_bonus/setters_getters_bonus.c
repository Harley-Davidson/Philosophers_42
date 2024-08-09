/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:06:33 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/09 15:06:34 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	res;

	mutex_handler(mutex, LOCK);
	res = *value;
	mutex_handler(mutex, UNLOCK);
	return (res);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	res;

	mutex_handler(mutex, LOCK);
	res = *value;
	mutex_handler(mutex, UNLOCK);
	return (res);
}

long	get_timestamp(t_time_measure tm)
{
	struct timeval	*tv;

	if (gettimeofday(&tv, NULL))
		return (GETTIME_ERROR);
	if (tm == SECOND)
		return (tv->tv_sec + (tv->tv_usec / 1000000));
	else if (tm == MILLIS)
		return (tv->tv_sec * 1000 + (tv->tv_usec / 1000));
	else if (tm == MILLIS)
		return (tv->tv_sec * 1000000 + (tv->tv_usec));
	return (NOT_REACHABLE_RET);
}
