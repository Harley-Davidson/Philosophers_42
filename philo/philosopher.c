/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:22:32 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/06 17:22:34 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	write_philo_state(t_philo *philo, t_philo_state state)
{
	long	elapsed;

	elapsed = get_timestamp(MILLIS) - philo->table->simul_start;
	mutex_handler(&(philo->table->write_mtx), LOCK);
	if (!is_simul_end(philo->table))
	{
		if (state == TAKE_FIRST_FORK || state == TAKE_SECOND_FORK)
			printf("%lu %lu has taken a fork\n", elapsed, philo->id);
		else if (state == EAT)
			printf("%lu %lu is eating\n", elapsed, philo->id);
		else if (state == SLEEP)
			printf("%lu %lu is sleeping\n", elapsed, philo->id);
		else if (state == THINK)
			printf("%lu %lu is thinking\n", elapsed, philo->id);
		else if (state == DIE)
			printf("%lu %lu died\n", elapsed, philo->id);
	}
	mutex_handler(&(philo->table->write_mtx), UNLOCK);
}

void	philo_usleep(long milisec, t_table *t)
{
	long	start;
	long	elapsed;
	long	remaining;
	long	usec;

	usec = milisec * 1000;
	start = get_timestamp(MICROS);
	while (get_timestamp(MICROS) - start < usec)
	{
		if (is_simul_end(t))
			break ;
		elapsed = get_timestamp(MICROS) - start;
		remaining = usec - elapsed;
		if (remaining > 1000)
			usleep(usec / 2);
		else
		{
			while (get_timestamp(MICROS) - start < usec)
				;
		}
	}
}

void	philo_eat(t_philo *philo)
{
	mutex_handler(&(philo->first_fork->fork_mtx), LOCK);
	write_philo_state(philo, TAKE_FIRST_FORK);
	if (philo->table->philo_nbr == 1)
	{
		mutex_handler(&(philo->first_fork->fork_mtx), UNLOCK);
		return ;
	}
	mutex_handler(&(philo->second_fork->fork_mtx), LOCK);
	write_philo_state(philo, TAKE_SECOND_FORK);
	write_philo_state(philo, EAT);
	set_long(&philo->philo_mtx, &philo->meal_timestamp, get_timestamp(MILLIS));
	philo->meals_cnt++;
	philo_usleep(philo->table->time_to_eat, philo->table);
	if (philo->meals_cnt == philo->table->meals_nbr_req)
		set_bool(&(philo->table->table_mtx), &philo->is_full, true);
	mutex_handler(&(philo->first_fork->fork_mtx), UNLOCK);
	mutex_handler(&(philo->second_fork->fork_mtx), UNLOCK);
}

void	philo_think(t_philo *philo, bool is_active)
{
	long	delay;

	if (is_active)
		write_philo_state(philo, THINK);
	delay = 2 * philo->table->time_to_eat - philo->table->time_to_sleep;
	if (delay < 0)
		delay = 0;
	if (philo->table->philo_nbr % 2 != 0)
	{
		if (philo->id % 2 != 0)
			philo_usleep(delay * 0.8, philo->table);
	}
}
