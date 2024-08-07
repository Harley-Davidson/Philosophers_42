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
	}
}

void	destroy_philos(t_table *t)
{

}
