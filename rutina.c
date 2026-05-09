/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutina.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:37:47 by bamdjar           #+#    #+#             */
/*   Updated: 2025/07/22 22:39:17 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_finito(t_shared *shared)
{
	bool	status;

	pthread_mutex_lock(&shared->finito_mutex);
	status = shared->finito;
	pthread_mutex_unlock(&shared->finito_mutex);
	return (status);
}

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->shared->finito_mutex);
	if (philo->shared->finito)
	{
		pthread_mutex_unlock(&philo->shared->finito_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->shared->print);
	printf("%ld %d %s\n", current_time() - philo->shared->inicio, philo->num
		+ 1, msg);
	pthread_mutex_unlock(&philo->shared->print);
	pthread_mutex_unlock(&philo->shared->finito_mutex);
}

void	forks(t_philo *philo)
{
	if (philo->num % 2 == 0)
		usleep(1000);
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
	}
	eat(philo);
	return ;
}

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken a fork");
	while (!is_finito(philo->shared))
		usleep(1000);
	pthread_mutex_unlock(philo->l_fork);
}

void	*rutina(void *arg)
{
	t_philo	*philo;
	bool	tmp;

	philo = (t_philo *)arg;
	if (philo->shared->n_philo == 1)
		return (one_philo(philo), NULL);
	while (!is_finito(philo->shared))
	{
		print_action(philo, "is thinking");
		forks(philo);
		if (philo->shared->n_eat > 0 && philo->n_eaten == philo->shared->n_eat)
		{
			pthread_mutex_lock(&philo->shared->death_mutex);
			philo->shared->n_death++;
			pthread_mutex_unlock(&philo->shared->death_mutex);
		}
		pthread_mutex_lock(&philo->shared->death_mutex);
		tmp = (philo->shared->n_death == philo->shared->n_philo);
		pthread_mutex_unlock(&philo->shared->death_mutex);
		if (tmp || is_finito(philo->shared))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}
