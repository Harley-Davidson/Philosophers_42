/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:35:19 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/07 23:35:21 by mvoloshy         ###   ########.fr       */
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
