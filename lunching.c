/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:37:26 by bamdjar           #+#    #+#             */
/*   Updated: 2025/07/22 22:39:06 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	timing(t_philo *thread, int n)
{
	int	i;

	thread[0].shared->inicio = current_time();
	i = 0;
	while (i < n)
	{
		thread[i].fasting = thread[0].shared->inicio;
		i++;
	}
	return ;
}

int	lunching(t_philo *thread, int n, pthread_t *philo)
{
	pthread_t	monitor;
	int			i;

	timing(thread, n);
	if (pthread_create(&monitor, NULL, death_monitor, thread) != 0)
		return (1);
	i = -1;
	while (++i < n)
	{
		if (pthread_create(&philo[i], NULL, rutina, &thread[i]) != 0)
			return (1);
	}
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	i = -1;
	while (++i < n)
	{
		if (pthread_join(philo[i], NULL) != 0)
			return (1);
	}
	return (0);
}
