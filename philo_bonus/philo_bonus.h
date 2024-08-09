/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:06:11 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/09 15:06:12 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>		//read, close, write
# include <stdlib.h>		//malloc
# include <stdbool.h>		//bool
# include <sys/time.h>		//time
# include <stdint.h>		//MAX/MIN ranges
# include <pthread.h>		//threads & mutex
# include <errno.h>			//to consume mutex errors

// Passing errors, for returns
enum e_err_state
{
	OK = 0,
	ARG_CNT_ERROR = 1,
	ARG_VAL_ERROR = 2,
	ALLOC_ERROR = 3,
	MUTEX_ERROR = 4,
	THREAD_ERROR = 5,
	GETTIME_ERROR = -1,
	NOT_REACHABLE_RET = 42,
};

// For mutex commands wrapper function
typedef enum e_command
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_command;

// For get time function
typedef enum e_time_measure
{
	SECOND,
	MILLIS,
	MICROS,
}	t_time_measure;

// For philo status
typedef enum e_philo_state
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIE,
}	t_philo_state;

// Fork - shared resource - Mutex struct
typedef struct s_fork
{
	pthread_mutex_t	fork_mtx;
	long			id;
}	t_fork;

typedef struct s_table	t_table;

// Philosopher struct
typedef struct s_philo
{
	pthread_mutex_t	philo_mtx;
	pthread_t		thread_id;
	long			id;
	long			meals_cnt;
	long			meal_timestamp;
	bool			is_full;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_table			*table;
}	t_philo;

// Key struct, which runs simulation
typedef struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_nbr_req;
	long			simul_start;
	bool			is_simul_end;
	bool			is_philos_ready;
	pthread_mutex_t	table_mtx;
	pthread_mutex_t	write_mtx;
	t_fork			*forks;
	t_philo			*philos;
}	t_table;

// TABLE.C:  initialization and freeing resources
int		parse_args(int argc, char **argv, t_table *t);
int		init_table(t_table *t);
void	init_philos(t_table *t);
void	clean_table(t_table *t);

// PHILOSOPHER.C:  Philosopher operations
void	write_philo_state(t_philo *philo, t_philo_state state);
void	philo_usleep(long usec, t_table *t);
void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);

// SIMULATION.C:  run actual simulation in multithreaded evironment
int		run_simulation(t_table *t);
bool	is_simul_end(t_table *t);
void	*fnc(void *arg);

// UTILS.C:
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		is_arg_err(char *s);
long	ft_atol(char *s);
void	*ft_calloc(size_t nmemb, size_t size);

// ERROR_HANDLERS.C: safe handlers to unify operations with threads and mutexes
int		mutex_handler(pthread_mutex_t *mtx, t_command cm);
int		pthread_handler(pthread_t *thread,
			void *(*routine)(void *), void *arg, t_command cm);
int		p_error(int err_id, t_table *t);

// SETTERS_GETTERS.C:  getters & setters to protect mutexes
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
long	get_timestamp(t_time_measure tm);

#endif
