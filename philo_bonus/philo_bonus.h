/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:11 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/21 15:24:12 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>     // read, close, write
# include <stdio.h>      // printf
# include <stdlib.h>     // malloc
# include <stdbool.h>    // bool
# include <sys/time.h>   // time
# include <stdint.h>     // MAX/MIN ranges
# include <pthread.h>    // threads & mutex
# include <errno.h>      // to consume mutex errors
# include <signal.h>     // for kill fnc
# include <sys/wait.h>   // for waitpid fnc
# include <semaphore.h> // for sem_open, sem_close, sem_post, sem_wait, etc
# include <fcntl.h>      // for O_CREAT and O_EXCL of sem_open fnc args

// Error handling states
enum e_err_state
{
	OK = 0,
	ARG_CNT_ERROR = 1,
	ARG_VAL_ERROR = 2,
	ALLOC_ERROR = 3,
	SEMAPHORE_ERROR = 4,
	FORK_ERROR = 5,
	WAIT_ERROR = 6,
	GETTIME_ERROR = -1,
	NOT_REACHABLE_RET = 42,
};

// Semaphore commands
typedef enum e_command
{
	WAIT,
	POST,
	INIT,
	DESTROY,
} t_command;

// Time measurement units
typedef enum e_time_measure
{
	SECOND,
	MILLIS,
	MICROS,
} t_time_measure;

// Philosopher states
typedef enum e_philo_state
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIE,
} t_philo_state;

// Fork - shared resource
typedef struct s_fork
{
	sem_t	fork_sem;
	long	id;
} t_fork;

typedef struct s_table t_table;

// Philosopher struct
typedef struct s_philo
{
	sem_t	philo_sem;
	pid_t	pid;
	long	id;
	long	meals_cnt;
	long	meal_timestamp;
	bool	is_full;
	t_fork	*forks;
	t_table	*table;
} t_philo;

// Key struct, which runs simulation
typedef struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals_nbr_req;
	long	simul_start;
	bool	is_simul_end;
	sem_t	*table_sem;
	sem_t	*write_sem;
	sem_t	*fork_sem;
	t_philo	*philos;
	pid_t 	checker_pid;
} t_table;

// Function declarations

// TABLE.C: Resources initialization and freeing resources
int		parse_args(int argc, char **argv, t_table *t);
int		init_table(t_table *t);
void	clean_table(t_table *t);

// PHILOSOPHER.C: Philosopher initialization & operations
void	init_philos(t_table *t);
void	write_philo_state(t_philo *philo, t_philo_state state);
void	philo_usleep(long usec, t_table *t);
void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo, bool is_active);

// SIMULATION.C: Run actual simulation in multithreaded environment
int		run_simulation(t_table *t);
bool	is_simul_end(t_table *t);
void	*philo_routine(void *arg);

// UTILS.C: Utility functions
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		is_arg_err(char *s);
long	ft_atol(char *s);
void	*ft_calloc(size_t nmemb, size_t size);

// ERROR_HANDLERS.C: Error handlers for threads and semaphores
int		sem_handler(sem_t *sem, t_command cm, int cnt);
int		p_error(int err_id, t_table *t);

// SETTERS_GETTERS.C: Getters & setters to protect mutexes
void	set_bool(sem_t *sem, bool *dest, bool value);
bool	get_bool(sem_t *sem, bool *value);
void	set_long(sem_t *sem, long *dest, long value);
long	get_long(sem_t *sem, long *value);
long	get_timestamp(t_time_measure tm);

#endif