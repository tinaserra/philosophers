/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaserra <tinaserra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:08:41 by vserra            #+#    #+#             */
/*   Updated: 2021/12/07 22:57:04 by tinaserra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check(t_env *bb, int *i)
{
	useconds_t time;

	pthread_mutex_lock(&bb->mutex);
	get_time_in_usec(&time);
	if (!bb->philo_died && !bb->ph[*i].eating && !bb->ph[*i].enough_eat
		&& (time - bb->ph[*i].last_time_eat) >= bb->time_to_die)
	{
		print_message(&(bb->ph[*i]), DIED);
		bb->philo_died = 1;
		pthread_mutex_unlock(&bb->mutex);
		pthread_mutex_unlock(&bb->death);
		return ;
		// pthread_exit(0);
	}
	if (bb->philo_died)
	{
		pthread_mutex_unlock(&bb->mutex);
		pthread_mutex_unlock(&bb->death);
		return ;
		// pthread_exit(0);
	}
	(*i)++;
	if (*i >= bb->nop && !bb->philo_died)
		*i = 0;
	pthread_mutex_unlock(&bb->mutex);
}

void	*death(void *data)
{
	t_env	*bb;
	int		i;

	bb = (t_env *)data;
	pthread_mutex_lock(&bb->death);
	i = 0;
	while (i < bb->nop)
	{
		check(bb, &i);
		usleep(100);
	}
	return (0);
}

int	create_philosophers(t_env *bb)
{
	int	i;

	if (pthread_create(&(bb->t_dead), NULL, &death, bb))
		return (-1);
	pthread_detach(bb->t_dead);
	i = 0;
	while (i < bb->nop)
	{
		pthread_create(&(bb->ph[i].thread), NULL, &justdoit, &bb->ph[i]);
		i++;
	}
	i = 0;
	while (i < bb->nop)
	{
		pthread_join(bb->ph[i].thread, NULL);
		i++;
	}
	// print_sumup(bb);
	return (0);
}
