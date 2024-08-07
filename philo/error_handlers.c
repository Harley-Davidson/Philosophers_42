/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:35:12 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/07 23:35:13 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_error(int err_id, t_table *t)
{
	if (err_id == ARG_CNT_ERROR)
		printf("Error:\nIncorrect number of arguments\n");
	else if (err_id == ARG_VAL_ERROR)
	{
		printf("Error:\nInvalid value of args (values are not integers or "
			"number of allowed meals or philosophers is incorrect.\n");
	}
	else if (err_id == ALLOC_ERROR)
		printf("Error:\nMemory allocation error\n");
	else if (err_id == MUTEX_ERROR)
		printf("Error:\nMutex error\n");
	else if (err_id == THREAD_ERROR)
		printf("Error:\nThread processing error\n");
	if (err_id == ALLOC_ERROR || err_id == MUTEX_ERROR
		|| err_id == THREAD_ERROR)
		clean_table(&t);
	return (err_id);
}

static int	mutex_error_handler(int state, t_command cm)
{
	if (state == 0)
		return (OK);
	if (state == EINVAL && (cm == LOCK || cm == UNLOCK))
		printf("Value specified by mutex is invalid.\n");
	else if (state == EINVAL && (cm == LOCK || cm == UNLOCK))
		printf("Value specified by attr is invalid.\n");
	else if (state == EDEADLK)
		printf("A deadlock condition was detected.\n");
	else if (state == EPERM)
		printf("The current thread does not own the mutex.\n");
	else if (state == ENOMEM)
		printf("Insufficient memory exists to initialize the mutex.\n");
	else if (state == EBUSY)
		printf("The mutex could not be acquired, it was already locked.\n");
	return (MUTEX_ERROR);
}

int	mutex_handler(pthread_mutex_t *mtx, t_command cm)
{
	if (cm == LOCK)
		return (mutex_error_handler(pthread_mutex_lock(mtx), LOCK));
	else if (cm == UNLOCK)
		return (mutex_error_handler(pthread_mutex_unload(mtx), UNLOCK));
	else if (cm == INIT)
		return (mutex_error_handler(pthread_mutex_init(mtx, NULL), INIT));
	else if (cm == DESTROY)
		return (mutex_error_handler(pthread_mutex_destroy(mtx), DESTROY));
}

static int	pthread_error_handler(int state, t_command cm)
{
	if (state == 0)
		return (OK);
	if (state == EAGAIN && cm == CREATE)
		printf("Insufficient resources to create another thread.\n");
	else if (state == EDEADLK && cm == JOIN)
		printf("A deadlock detected or thread specifies a calling thread.\n");
	else if (state == EINVAL && (cm == JOIN || DETACH))
		printf("A thread is not a joinable thread.\n");
	else if (state == ESRCH && (cm == JOIN || DETACH))
		printf("No thread with the ID thread could be found.\n");
	return (THREAD_ERROR);
}

int	pthread_handler(pthread_t *thread,
			void *(*routine)(void *), void *arg, t_command cm)
{
	if (cm == CREATE)
		return (pthread_error_handler(pthread_create(thread, NULL,
					routine, arg), CREATE));
	else if (cm == JOIN)
		return (pthread_error_handler(pthread_join(thread, NULL), JOIN));
	else if (cm == DETACH)
		return (pthread_error_handler(pthread_detach(thread), DETACH));
}
