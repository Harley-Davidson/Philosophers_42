/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:06:23 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/09 15:06:25 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_philo_state(t_philo *philo, t_philo_state state)
{
	if (philo->is_full)
		return ;
	mutex_handler(&(philo->table->write_mtx), LOCK);
	if (!is_simul_end(philo->table))
	{
		// if (state == TAKE_FIRST_FORK || state == TAKE_SECOND_FORK)
		// printf("%lu %d has taken a fork\n", get_timestamp(MILLISECOND)
		//			, philo->id);
		if (state == TAKE_FIRST_FORK || state == TAKE_SECOND_FORK)
			printf("%lu %d has taken a first fork with id: %d\n",
				get_timestamp(MILLIS), philo->id, philo->first_fork->id);
		if (state == TAKE_FIRST_FORK || state == TAKE_SECOND_FORK)
			printf("%lu %d has taken a second fork with id: %d\n",
				get_timestamp(MILLIS), philo->id, philo->first_fork->id);
		else if (state == EAT)
			printf("%lu %d is eating\n", get_timestamp(MILLIS), philo->id);
		else if (state == SLEEP)
			printf("%lu %d is sleeping\n", get_timestamp(MILLIS), philo->id);
		else if (state == THINK)
			printf("%lu %d is thinking\n", get_timestamp(MILLIS), philo->id);
		else if (state == DIE)
			printf("%lu %d  died\n", get_timestamp(MILLIS), philo->id);
	}
	mutex_handler(&(philo->table->write_mtx), UNLOCK);
}

void	philo_usleep(long usec, t_table *t)
{
	long	start;

	start = get_timestamp(MICROS);
	while (get_timestamp(MICROS) - start < usec)
		;
}

void	philo_eat(t_philo *philo)
{
	mutex_handler(&(philo->first_fork->fork_mtx), LOCK);
	write_philo_state(philo, TAKE_FIRST_FORK);
	mutex_handler(&(philo->second_fork->fork_mtx), LOCK);
	write_philo_state(philo, TAKE_SECOND_FORK);
	write_philo_state(philo, EAT);
	set_long(&philo->philo_mtx, philo->meal_timestamp, get_timestamp(MILLIS));
	philo->meals_cnt++;
	philo_usleep(philo->table->time_to_eat, philo->table);
	if (philo->meals_cnt == philo->table->meals_nbr_req)
		set_bool(&(philo->table->table_mtx), philo->is_full, true);
	mutex_handler(&(philo->first_fork->fork_mtx), UNLOCK);
	mutex_handler(&(philo->second_fork->fork_mtx), UNLOCK);
}

void	philo_think(t_philo *philo)
{
	write_philo_state(philo, THINK);
}
