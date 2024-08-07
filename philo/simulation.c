/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:55:16 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/07 20:55:17 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simul_end(t_table *t)
{
	return (get_bool(&(t->mtx), t->is_simul_end));
}

void	*fnc(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	return (NULL);
}

int	run_simulation(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_nbr)
	{
		if (i == 0)
			t->simul_start = (long)time(NULL) * 1000;
		if (pthread_handler(&(t->philos[i].thread_id),
				fnc, &t->philos[i], CREATE) != OK)
			return (THREAD_ERROR);
	}
	i = -1;
	while (++i < t->philo_nbr)
	{
		if (pthread_handler(&(t->philos[i].thread_id), NULL, NULL, JOIN) != OK)
			return (THREAD_ERROR);
	}
}
