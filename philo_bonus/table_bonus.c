/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:35 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/21 15:24:36 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse_args(int argc, char **argv, t_table *t)
{
	int	i;

	i = 0;
	t->meals_nbr_req = -1;
	while (++i < argc)
	{
		while (ft_isspace(*(argv[i])))
			(argv[i])++;
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
	if (t->philo_nbr < 1)
		return (ARG_VAL_ERROR);
	return (OK);
}

int	init_table(t_table *t)
{
	sem_unlink("/fork_sem");
	sem_unlink("/table_sem");
	sem_unlink("/write_sem");
	t->fork_sem = sem_open("/fork_sem", O_CREAT, 0644, t->philo_nbr - 1);
	t->table_sem = sem_open("/table_sem", O_CREAT, 0644, 1);
	t->write_sem = sem_open("/write_sem", O_CREAT, 0644, 1);
	if (t->fork_sem == SEM_FAILED || t->table_sem == SEM_FAILED
		|| t->write_sem == SEM_FAILED)
		return (SEMAPHORE_ERROR);
	t->philos = ft_calloc(t->philo_nbr, sizeof(t_philo));
	if (t->philos == NULL)
		return (ALLOC_ERROR);
	t->is_simul_end = false;
	init_philos(t);
	return (OK);
}

void	clean_table(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_nbr)
		sem_handler(&t->philos[i].philo_sem, DESTROY, 0);
	sem_unlink("/fork_sem");
	sem_unlink("/table_sem");
	sem_unlink("/write_sem");
	free(t->philos);
}