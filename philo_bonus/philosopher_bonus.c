/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:02 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/21 15:24:04 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		sem_handler(&(t->philos[i].philo_sem), INIT, 1);
		set_long(&t->philos[i].philo_sem, &t->philos[i].meal_timestamp, get_timestamp(MILLIS));
	}
}

void	write_philo_state(t_philo *philo, t_philo_state state)
{
	long	elapsed;

	elapsed = get_timestamp(MILLIS) - philo->table->simul_start;
	sem_handler(&philo->philo_sem, WAIT, 0);
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
	sem_handler(&philo->philo_sem, POST, 0);
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
	sem_handler(philo->table->fork_sem, WAIT, 0);
	write_philo_state(philo, TAKE_FIRST_FORK);
	sem_handler(philo->table->fork_sem, WAIT, 0);
	write_philo_state(philo, TAKE_SECOND_FORK);
	write_philo_state(philo, EAT);
	set_long(&philo->philo_sem, &philo->meal_timestamp, get_timestamp(MILLIS));
	// printf("PHILO %ld meal time: %ld\n", philo->id, get_long(&philo->philo_sem, &philo->meal_timestamp) - get_long(&philo->table->table_sem, &philo->table->simul_start));
	philo->meals_cnt++;
	philo_usleep(philo->table->time_to_eat, philo->table);
	if (philo->meals_cnt == philo->table->meals_nbr_req)
	{
		set_bool(philo->table->table_sem, &philo->is_full, true);
		printf("PHILO %ld GOT FULL\n", philo->id);
	}
	sem_handler(philo->table->fork_sem, POST, 0);
	sem_handler(philo->table->fork_sem, POST, 0);
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