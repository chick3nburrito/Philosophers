/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutina_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:51:04 by bamdjar           #+#    #+#             */
/*   Updated: 2025/07/24 22:51:18 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->shared->t_sleep, philo);
	if (philo->shared->t_eat > philo->shared->t_sleep && philo->shared->n_philo
		% 2 != 0)
	{
		ft_usleep(philo->shared->t_eat, philo);
	}
}

void	eat(t_philo *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->access_mutex);
	philo->fasting = current_time();
	pthread_mutex_unlock(&philo->access_mutex);
	ft_usleep(philo->shared->t_eat, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->n_eaten++;
}

void	*death_monitor(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (!is_finito(philos[0].shared))
	{
		i = 0;
		while (i < philos[0].shared->n_philo)
		{
			if (death_check(&philos[i]))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

void	print_death(t_philo *philo, long now)
{
	philo->shared->finito = true;
	pthread_mutex_lock(&philo->shared->death_mutex);
	if (philo->shared->n_eat == -1
		|| philo->shared->n_philo != philo->shared->n_death)
	{
		pthread_mutex_lock(&philo->shared->print);
		printf("%ld %d died\n", now - philo->shared->inicio, philo->num + 1);
		pthread_mutex_unlock(&philo->shared->print);
	}
	pthread_mutex_unlock(&philo->shared->death_mutex);
}

int	death_check(t_philo *philo)
{
	long	fasting;
	long	now;

	pthread_mutex_lock(&philo->access_mutex);
	fasting = philo->fasting;
	pthread_mutex_unlock(&philo->access_mutex);
	now = current_time();
	if ((now - fasting) >= philo->shared->t_die)
	{
		pthread_mutex_lock(&philo->shared->finito_mutex);
		print_death(philo, now);
		pthread_mutex_unlock(&philo->shared->finito_mutex);
		return (1);
	}
	return (0);
}
