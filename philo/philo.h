/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:21:48 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/06 17:21:49 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>		//read, close, write
# include <stdlib.h>		//malloc
# include <stdbool.h>		//bool
# include <time.h>			//time
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

// Fork - shared resource - Mutex struct
typedef struct s_fork
{
	pthread_mutex_t	mtx;
	long			id;
}	t_fork;

typedef struct s_table	t_table;

// Philosopher struct
typedef struct s_philo
{
	pthread_t	thread_id;
	long		id;
	long		meals_cnt;
	long		meal_timestamp;
	bool		is_full;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
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
	pthread_mutex_t	mtx;
	t_fork			*forks;
	t_philo			*philos;
}	t_table;

// Initialization and freeing resources
int		parse_args(int argc, char **argv, t_table *t);
int		init_table(t_table *t);
void	init_philos(t_table *t);
void	destroy_philos(t_table *t);
void	clean_table(t_table *t);

// Simulation
int		run_simulation(t_table *t);
bool	is_simul_end(t_table *t);

// Utils
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		is_arg_err(char *s);
long	ft_atol(char *s);
//int		ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		p_error(int err_id, t_table *t);

// Handlers, getters & setters
int		mutex_handler(pthread_mutex_t *mtx, t_command cm);
int		pthread_handler(pthread_t *thread,
			void *(*routine)(void *), void *arg, t_command cm);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);

#endif
