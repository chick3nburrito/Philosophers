/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:37:41 by bamdjar           #+#    #+#             */
/*   Updated: 2025/07/22 22:39:14 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_shared
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	pthread_mutex_t	*forks;
	long			inicio;
	bool			finito;
	pthread_mutex_t	finito_mutex;
	pthread_mutex_t	print;
	int				n_death;
	pthread_mutex_t	death_mutex;
}					t_shared;

typedef struct s_philo
{
	int				num;
	t_shared		*shared;
	long			fasting;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				n_eaten;
	pthread_mutex_t	access_mutex;
}					t_philo;

long				current_time(void);
int					is_finito(t_shared *shared);
int					death_check(t_philo *philo);
void				print_action(t_philo *philo, char *msg);
void				*rutina(void *arg);
int					lunching(t_philo *thread, int n, pthread_t *philo);
int					assign_data(t_shared *shared, char **args,
						t_philo *threads);
int					ft_atoi(char *str);
int					cleanup(t_shared *shared, t_philo *philos);

void				*death_monitor(void *arg);

void				eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				forks(t_philo *philo);
void				ft_usleep(long time_to, t_philo *philo);

#endif
