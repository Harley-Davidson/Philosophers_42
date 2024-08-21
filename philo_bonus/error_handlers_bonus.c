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

int p_error(int err_id, t_table *t)
{
    if (err_id == OK)
        return (OK);
    if (err_id == ARG_CNT_ERROR)
        printf("Error: Invalid number of arguments.\n");
    else if (err_id == ARG_VAL_ERROR)
        printf("Error: Invalid argument value.\n");
    else if (err_id == ALLOC_ERROR)
        printf("Error: Memory allocation failed.\n");
    else if (err_id == SEMAPHORE_ERROR)
        printf("Error: Semaphore operation failed.\n");
    else if (err_id == FORK_ERROR)
        printf("Error: Process creation (fork) failed.\n");
    clean_table(t);
    return (err_id);
}

static int sem_error_handler(int state, t_command cm)
{
    if (state == 0)
        return (OK);
    if (state == EINVAL && (cm == WAIT || cm == POST))
        printf("Semaphore error: Invalid semaphore value.\n");
    else if (state == EINVAL && cm == INIT)
        printf("Semaphore error: Invalid attribute for initialization.\n");
    else if (state == EDEADLK)
        printf("Semaphore error: A deadlock condition was detected.\n");
    else if (state == EPERM)
        printf("Semaphore error: The current process does not own the semaphore.\n");
    else if (state == ENOMEM)
        printf("Semaphore error: Insufficient memory to initialize semaphore.\n");
    return (SEMAPHORE_ERROR);
}

int sem_handler(sem_t *sem, t_command cm)
{
    if (cm == WAIT)
        return (sem_error_handler(sem_wait(sem), WAIT));
    else if (cm == POST)
        return (sem_error_handler(sem_post(sem), POST));
    else if (cm == INIT)
        return (sem_error_handler(sem_init(sem, 1, 1), INIT));
    else if (cm == DESTROY)
        return (sem_error_handler(sem_destroy(sem), DESTROY));
    return (OK);
}

int process_error_handler(int err_code)
{
    if (err_code == -1)
    {
        if (errno == EAGAIN)
            printf("Process error: Insufficient resources to create a process.\n");
        else if (errno == ENOMEM)
            printf("Process error: Insufficient memory to create a process.\n");
        else if (errno == ENOSYS)
            printf("Process error: System lacks support for process creation.\n");
        else
            printf("Process error: An unknown error occurred.\n");
        return (FORK_ERROR);
    }
    return (OK);
}