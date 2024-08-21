/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:41 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/08/21 15:24:43 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c <= 32)
		return (1);
	return (0);
}

int	is_arg_err(char *s)
{
	int	i;

	if (*s == '\0')
		return (ARG_VAL_ERROR);
	i = 0;
	if (*s == '+')
		s++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (ARG_VAL_ERROR);
		i++;
	}
	if (i > 10)
		return (ARG_VAL_ERROR);
	return (OK);
}

long	ft_atol(char *s)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (s[i])
	{
		res = 10 * res + (s[i] - 48);
		i++;
	}
	return (res);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			total_size;
	unsigned char	*t;

	if (nmemb && size && nmemb > (SIZE_MAX / size))
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	t = ptr;
	while (total_size > 0)
	{
		*t = '\0';
		t++;
		total_size--;
	}
	return (ptr);
}
