/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:37:00 by bamdjar           #+#    #+#             */
/*   Updated: 2025/07/22 22:39:03 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_shared *shared)
{
	int	i;

	if (pthread_mutex_init(&shared->print, NULL))
		return (0);
	if (pthread_mutex_init(&shared->finito_mutex, NULL))
		return (pthread_mutex_destroy(&shared->print), 0);
	if (pthread_mutex_init(&shared->death_mutex, NULL))
	{
		pthread_mutex_destroy(&shared->print);
		pthread_mutex_destroy(&shared->finito_mutex);
		return (0);
	}
	shared->forks = malloc(sizeof(pthread_mutex_t) * shared->n_philo);
	if (!shared->forks)
		return (0);
	i = 0;
	while (i < shared->n_philo)
	{
		if (pthread_mutex_init(&shared->forks[i], NULL))
			return (free(shared->forks), 0);
		i++;
	}
	return (1);
}

void	cmd_args(t_shared *shared, char **args)
{
	shared->n_philo = ft_atoi(args[0]);
	shared->t_die = ft_atoi(args[1]);
	shared->t_eat = ft_atoi(args[2]);
	shared->t_sleep = ft_atoi(args[3]);
	shared->finito = false;
	shared->n_death = 0;
	if (!args[4])
		shared->n_eat = -1;
	else
		shared->n_eat = ft_atoi(args[4]);
}

int	assign_data(t_shared *shared, char **args, t_philo *threads)
{
	int	i;

	cmd_args(shared, args);
	if (!init_mutexes(shared))
		return (0);
	i = 0;
	while (i < shared->n_philo)
	{
		threads[i].num = i;
		threads[i].shared = shared;
		threads[i].l_fork = &shared->forks[i];
		threads[i].r_fork = &shared->forks[(i + 1) % shared->n_philo];
		threads[i].fasting = 0;
		threads[i].n_eaten = 0;
		if (pthread_mutex_init(&threads[i].access_mutex, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&threads[i].access_mutex);
			return (0);
		}
		i++;
	}
	return (1);
}
