/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:06:40 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/09 15:06:41 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simul_end(t_table *t)
{
	return (get_bool(&(t->table_mtx), t->is_simul_end));
}

void	*fnc(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_bool(&philo->table->table_mtx, philo->table->is_philos_ready))
		;
	while (!is_simul_end(philo->table))
	{
		if (philo->is_full)
			break ;
		philo_eat(philo);
		write_philo_state(philo, SLEEP);
		philo_usleep(philo->table->time_to_sleep, philo->table);
		philo_think(philo);
	}
}

int	run_simulation(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_nbr)
	{
		if (pthread_handler(&(t->philos[i].thread_id),
				fnc, &t->philos[i], CREATE) != OK)
			return (THREAD_ERROR);
	}
	t->simul_start = get_timestamp(MILLIS);
	set_bool(&t->table_mtx, t->is_philos_ready, true);
	i = -1;
	while (++i < t->philo_nbr)
	{
		if (pthread_handler(&(t->philos[i].thread_id), NULL, NULL, JOIN) != OK)
			return (THREAD_ERROR);
	}
}
