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
	return (get_bool(&(t->table_mtx), &t->is_simul_end));
}

bool	is_dead(t_philo *philo)
{
	return (get_timestamp(MILLIS) - get_long(&philo->philo_mtx,
			&philo->meal_timestamp) > philo->table->time_to_die);
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_bool(&philo->table->table_mtx, &philo->table->is_philos_ready))
		;
	set_long(&philo->philo_mtx, &philo->meal_timestamp, get_timestamp(MILLIS));
	philo_think(philo, false);
	while (!is_simul_end(philo->table))
	{
		philo_eat(philo);
		write_philo_state(philo, SLEEP);
		philo_usleep(philo->table->time_to_sleep, philo->table);
		philo_think(philo, true);
	}
	return (NULL);
}

void	*checker_thread(void *arg)
{
	t_table	*t;
	int		i;
	int		cnt;

	t = (t_table *)arg;
	while (!get_bool(&t->table_mtx, &t->is_philos_ready))
		;
	while (!is_simul_end(t))
	{
		i = -1;
		cnt = 0;
		while (++i < t->philo_nbr && !is_simul_end(t))
		{
			if (is_dead(&t->philos[i]))
			{
				write_philo_state(&(t->philos[i]), DIE);
				set_bool(&t->table_mtx, &t->is_simul_end, true);
			}
			if (get_bool(&t->philos[i].philo_mtx, &t->philos[i].is_full))
				cnt++;
			if (cnt == t->philo_nbr)
				set_bool(&t->table_mtx, &t->is_simul_end, true);
		}
	}
	return (NULL);
}

int	run_simulation(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_nbr)
	{
		if (pthread_handler(&(t->philos[i].thread_id),
				philo_thread, &t->philos[i], CREATE) != OK)
			return (THREAD_ERROR);
	}
	t->simul_start = get_timestamp(MILLIS);
	set_bool(&t->table_mtx, &t->is_philos_ready, true);
	if (pthread_handler(&(t->checker), checker_thread, t, CREATE) != OK)
		return (THREAD_ERROR);
	i = -1;
	while (++i < t->philo_nbr)
	{
		if (pthread_handler(&(t->philos[i].thread_id), NULL, NULL, JOIN) != OK)
			return (THREAD_ERROR);
	}
	if (pthread_handler(&(t->checker), NULL, NULL, JOIN) != OK)
		return (THREAD_ERROR);
	return (OK);
}
