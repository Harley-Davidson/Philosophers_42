/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:21:26 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/06 17:21:32 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	t;
	int		is_err;

	if (argc < 5 || argc > 6)
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
