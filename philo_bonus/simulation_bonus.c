/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:21 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/21 15:24:22 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	is_simul_end(t_table *t)
{
	return (get_bool(t->table_sem, &t->is_simul_end));
}

bool	is_dead(t_philo *philo)
{
	return (get_timestamp(MILLIS) - get_long(&philo->philo_sem,
			&philo->meal_timestamp) > philo->table->time_to_die);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// set_long(&philo->philo_sem, &philo->meal_timestamp, get_timestamp(MILLIS));
	philo_think(philo, false);
	while (!is_simul_end(philo->table))
	{
		printf("\nPHILO %ld IS SIMUL END : %d\n",philo->id, get_bool(philo->table->table_sem, &philo->table->is_simul_end));
		// if (get_bool(philo->table->table_sem, philo->table->is_simul_end))
		//     break;
		philo_eat(philo);
		write_philo_state(philo, SLEEP);
		philo_usleep(philo->table->time_to_sleep, philo->table);
		philo_think(philo, true);
		// if (is_dead(philo))
		// {
		// 	write_philo_state(philo, DIE);
		// 	set_bool(philo->table->table_sem, philo->table->is_simul_end, true);
		// 	printf("\nPHILO %ld IS SIMUL END : %d\n",philo->id, get_bool(philo->table->table_sem, philo->table->is_simul_end));
		// }
			
	}
	return (NULL);
}


int	run_simulation(t_table *t)
{
	pid_t	pid;
	int		i;
	int		cnt;

	i = -1;
	t->simul_start = get_timestamp(MILLIS);
	while (++i < t->philo_nbr)
	{
		pid = fork();
		if (pid < 0)
			return (p_error(FORK_ERROR, t));
		if (pid == 0)
		{
			t->philos[i].pid = pid;
			philo_routine(&(t->philos[i]));
			exit(0);
		}
	}
	cnt = 0;
	while (!is_simul_end(t))
	{
		i = -1;
		cnt = 0;
		while (++i < t->philo_nbr )
		{
			if (is_dead(&t->philos[i]) && !is_simul_end(t))
			{
				write_philo_state(&(t->philos[i]), DIE);
				set_bool(t->table_sem, &t->is_simul_end, true);
				printf("\n IS SIMUL END : %d\n", t->is_simul_end);
			}
			if (get_bool(&t->philos[i].philo_sem, &t->philos[i].is_full))
			{
				cnt++;
				printf("CNT OF FULL FILOS: %d", cnt);
			}
			if (cnt == t->philo_nbr)
				set_bool(t->table_sem, &t->is_simul_end, true);
		}
	}
	i = -1;
	while (++i < t->philo_nbr)
	{
		if (waitpid(t->philos[i].pid, NULL, 0) < 0)
			return p_error(WAIT_ERROR, t);
	}
	return (OK);
}