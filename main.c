/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:37:33 by bamdjar           #+#    #+#             */
/*   Updated: 2025/07/22 22:39:10 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valide_input(int arc, char **arv)
{
	int	i;

	if (!(arc == 5 || arc == 6))
		return (1);
	i = 1;
	while (i < arc)
	{
		if (ft_atoi(arv[i]) <= 0)
			return (1);
		i++;
	}
	if (ft_atoi(arv[1]) > 200)
		return (1);
	return (0);
}

int	main(int arc, char **arv)
{
	t_shared	shared;
	t_philo		*thread;
	pthread_t	*philo;

	if (valide_input(arc, arv))
		return (printf("Error: invalid input\n"), 1);
	philo = malloc(sizeof(pthread_t) * ft_atoi(arv[1]));
	if (!philo)
		return (1);
	thread = malloc(sizeof(t_philo) * ft_atoi(arv[1]));
	if (!thread)
		return (free(philo), 1);
	if (!assign_data(&shared, arv + 1, thread))
	{
		return (free(philo), cleanup(&shared, thread), 1);
	}
	if (lunching(thread, shared.n_philo, philo))
		return (free(philo), cleanup(&shared, thread), 1);
	if (cleanup(&shared, thread))
		return (1);
	free(philo);
	return (0);
}
