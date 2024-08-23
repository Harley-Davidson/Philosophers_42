/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:23:53 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/21 15:23:54 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	p_error(int err_id, t_table *t)
{
	if (err_id == ARG_CNT_ERROR)
		printf("Error:\nIncorrect number of arguments\n");
	else if (err_id == ARG_VAL_ERROR)
	{
		printf("Error:\nInvalid value of args (values are not integers or "
			"number of allowed meals or philosophers is incorrect).\n");
	}
	else if (err_id == ALLOC_ERROR)
		printf("Error:\nMemory allocation error\n");
	else if (err_id == SEMAPHORE_ERROR)
		printf("Error:\nSemaphore error\n");
	else if (err_id == FORK_ERROR)
		printf("Error:\nForking error\n");
	else if (err_id == WAIT_ERROR)
		printf("Error:\nWait error\n");
	else if (err_id == GETTIME_ERROR)
		printf("Error:\nNot able to get timestamp error\n");
	if (err_id == ALLOC_ERROR || err_id == FORK_ERROR || err_id == WAIT_ERROR
		|| err_id == SEMAPHORE_ERROR || err_id == GETTIME_ERROR)
		clean_table(t);
	return (err_id);
}

static int sem_error_handler(int state, t_command cm)
{
    if (state == 0)
        return (OK);
    if (state == EINVAL && (cm == WAIT || cm == POST))
        printf("Value specified by semaphore is invalid.\n");
    else if (state == EAGAIN)
        printf("The semaphore could not be acquired, it was already locked.\n");
    else if (state == ENOMEM)
        printf("Insufficient memory exists to initialize the semaphore.\n");
    return (SEMAPHORE_ERROR);
}

int sem_handler(sem_t *sem, t_command cm, int cnt)
{
    if (cm == WAIT)
        return (sem_error_handler(sem_wait(sem), WAIT));
    else if (cm == POST)
        return (sem_error_handler(sem_post(sem), POST));
    else if (cm == INIT)
        return (sem_error_handler(sem_init(sem, 0, cnt), INIT)); 
    else if (cm == DESTROY)
        return (sem_error_handler(sem_destroy(sem), DESTROY));
    return (OK);
}