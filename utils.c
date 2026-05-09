/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:37:54 by bamdjar           #+#    #+#             */
/*   Updated: 2025/07/22 22:39:19 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atoi(char *str)
{
	long	res;

	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			return (-1);
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	while (*str)
	{
		if (*str != ' ' || *str != '\t')
			return (-1);
		str++;
	}
	return (res);
}

int	cleanup(t_shared *shared, t_philo *philos)
{
	int	i;

	i = 0;
	if (shared->forks)
	{
		while (i < shared->n_philo)
		{
			if (pthread_mutex_destroy(&shared->forks[i]) != 0)
				return (1);
			i++;
		}
		free(shared->forks);
	}
	if (pthread_mutex_destroy(&shared->print) != 0
		|| pthread_mutex_destroy(&shared->finito_mutex) != 0
		|| pthread_mutex_destroy(&shared->death_mutex) != 0)
		return (1);
	i = 0;
	while (i < shared->n_philo)
	{
		if (0 != pthread_mutex_destroy(&philos[i].access_mutex))
			return (1);
		i++;
	}
	return (free(philos), 0);
}

void	ft_usleep(long time_to, t_philo *philo)
{
	long	start;
	long	end;

	start = current_time();
	end = start + time_to;
	while (current_time() < end)
	{
		if (is_finito(philo->shared))
			break ;
		usleep(500);
	}
}
