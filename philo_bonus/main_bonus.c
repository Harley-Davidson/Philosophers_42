/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:05:59 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/09 15:06:00 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	t;
	int		is_err;

	if (argc != 4 || argc != 5)
		return (p_error(ARG_CNT_ERROR, &t));
	else
	{
		is_err = parse_args(argc, argv, &t);
		if (is_err)
			return (p_error(is_err, &t));
		is_err = init_table(&t);
		if (is_err)
			return (p_error(is_err, &t));
		is_err = run_simulation(&t);
		if (is_err)
			return (p_error(is_err, &t));
		clean_table(&t);
	}
}
