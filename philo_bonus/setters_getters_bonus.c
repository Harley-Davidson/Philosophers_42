/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:28 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/21 15:24:29 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_bool(sem_t *sem, bool *dest, bool value)
{
	sem_handler(sem, WAIT);
	*dest = value;
	sem_handler(sem, POST);
}

bool	get_bool(sem_t *sem, bool *value)
{
	bool	result;

	sem_handler(sem, WAIT);
	result = *value;
	sem_handler(sem, POST);
	return (result);
}

void	set_long(sem_t *sem, long *dest, long value)
{
	sem_handler(sem, WAIT);
	*dest = value;
	sem_handler(sem, POST);
}

long	get_long(sem_t *sem, long *value)
{
	long	result;

	sem_handler(sem, WAIT);
	result = *value;
	sem_handler(sem, POST);
	return (result);
}

long	get_timestamp(t_time_measure tm)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (GETTIME_ERROR);
	if (tm == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (tm == MILLIS)
		return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
	else if (tm == MICROS)
		return (tv.tv_sec * 1000000 + (tv.tv_usec));
	return (NOT_REACHABLE_RET);
}
