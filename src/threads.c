/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaserra <tinaserra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:08:41 by vserra            #+#    #+#             */
/*   Updated: 2021/12/16 23:25:13 by tinaserra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	check_death(t_env *bb, int *i, int eating, useconds_t last_time_eat)
// {
// 	useconds_t	time;

// 	get_time_in_usec(&time);
// 	if (!bb->philo_died && !eating && !bb->ph[*i].enough_eat
// 		&& (time - last_time_eat) >= bb->time_to_die)
// 	{
// 		print_message(&bb->ph[*i], DIED);
// 		pthread_mutex_lock(&bb->died);
// 		bb->philo_died = 1;
// 		pthread_mutex_unlock(&bb->died);
// 		pthread_mutex_unlock(&bb->mutex);
// 		pthread_mutex_unlock(&bb->death);
// 		return (-1);
// 	}
// 	return (0);
// }

static int	check_eat(t_env *bb, int *i)
{
	int			tmp_eating;
	int			tmp_nb_time_eat;
	useconds_t	tmp_last_time_eat;
	useconds_t	time;

	pthread_mutex_lock(&bb->mutex);
	pthread_mutex_lock(&bb->ph[*i].mutex_eating);
	tmp_eating = bb->ph[*i].eating;
	tmp_last_time_eat = bb->ph[*i].last_time_eat;
	tmp_nb_time_eat = bb->ph[*i].nb_time_eat;
	pthread_mutex_unlock(&bb->ph[*i].mutex_eating);
	// if (check_death(bb, i, tmp_eating, tmp_last_time_eat) == -1)
	// 	return (-1);

	get_time_in_usec(&time);
	if (!bb->philo_died && !tmp_eating && !bb->ph[*i].enough_eat
		&& (time - tmp_last_time_eat) >= bb->time_to_die)
	{
		print_message(&bb->ph[*i], DIED);
		pthread_mutex_lock(&bb->died);
		bb->philo_died = 1;
		pthread_mutex_unlock(&bb->died);
		pthread_mutex_unlock(&bb->mutex);
		pthread_mutex_unlock(&bb->death);
		return (-1);
	}

	if (bb->notep_must_eat == 0 || tmp_nb_time_eat < bb->notep_must_eat)
		bb->enough_eat = 0;
	(*i)++;
	pthread_mutex_unlock(&bb->mutex);
	return (0);
}

static void	death(t_env *bb)
{
	int		i;

	pthread_mutex_lock(&bb->death);
	pthread_mutex_unlock(&bb->create);
	i = 0;
	bb->enough_eat = 1;
	while (i < bb->nop)
	{
		if (check_eat(bb, &i) == -1)
			break ;
		usleep(100);
		if (i >= bb->nop && !bb->philo_died)
		{
			if (bb->enough_eat == 1)
			{
				pthread_mutex_lock(&bb->died);
				bb->philo_died = 1;
				pthread_mutex_unlock(&bb->died);
				break ;
			}
			i = 0;
			bb->enough_eat = 1;
		}
	}
	return ;
}

int	create_philosophers(t_env *bb)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&bb->create);
	while (i < bb->nop)
	{
		pthread_create(&(bb->ph[i].thread), NULL, &justdoit, &bb->ph[i]);
		i++;
	}
	i = 0;
	death(bb);
	while (i < bb->nop)
	{
		pthread_join(bb->ph[i].thread, NULL);
		i++;
	}
	return (0);
}
