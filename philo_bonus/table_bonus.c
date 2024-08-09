/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:06:49 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/09 15:06:50 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, t_table *t)
{
	int	i;

	i = 0;
	t->meals_nbr_req = -1;
	while (++i <= argc)
	{
		while (ft_isspace(*argv[i]))
			argv[i]++;
		if (is_arg_err(argv[i]) != 0 || ft_atol(argv[i]) >= INT32_MAX)
			return (ARG_VAL_ERROR);
		if (i == 1)
			t->philo_nbr = ft_atol(argv[i]);
		else if (i == 2)
			t->time_to_die = ft_atol(argv[i]);
		else if (i == 3)
			t->time_to_eat = ft_atol(argv[i]);
		else if (i == 4)
			t->time_to_sleep = ft_atol(argv[i]);
		else if (i == 5)
			t->meals_nbr_req = ft_atol(argv[i]);
	}
	if (t->meals_nbr_req == 0 || t->philo_nbr < 2)
		return (ARG_VAL_ERROR);
	return (OK);
}

int	init_table(t_table *t)
{
	int	i;

	t->is_simul_end = false;
	t->is_philos_ready = false;
	if (mutex_handler(&t->table_mtx, INIT) != OK)
		return (MUTEX_ERROR);
	t->philos = ft_calloc(t->philo_nbr, sizeof(t_philo));
	if (t->philos == NULL)
		return (ALLOC_ERROR);
	t->forks = ft_calloc(t->philo_nbr, sizeof(t_fork));
	if (t->forks == NULL)
		return (ALLOC_ERROR);
	i = -1;
	while (++i < t->philo_nbr)
	{
		if (mutex_handler(&t->forks[i].fork_mtx, INIT) != OK)
			return (MUTEX_ERROR);
		t->forks[i].id = i;
	}
	init_philos(t);
	return (OK);
}

void	init_philos(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_nbr)
	{
		t->philos[i].meals_cnt = 0;
		t->philos[i].is_full = false;
		t->philos[i].table = t;
		t->philos[i].id = i + 1;
		t->philos[i].first_fork = &(t->forks[i]);
		t->philos[i].second_fork = &(t->forks[(i + 1) % t->philo_nbr]);
		if (t->philos[i].id % 2 == 0)
		{
			t->philos[i].first_fork = &(t->forks[(i + 1) % t->philo_nbr]);
			t->philos[i].second_fork = &(t->forks[i]);
		}
		mutex_handler(&(t->philos[i].philo_mtx), INIT);
	}
}

void	clean_table(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_nbr)
	{
		if (!t->forks[i].id)
			break ;
		mutex_handler(&t->forks[i].fork_mtx, DESTROY);
	}
	free(t->philos);
	free(t->forks);
}
