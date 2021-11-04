/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:08:41 by vserra            #+#    #+#             */
/*   Updated: 2021/11/03 17:32:25 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check(t_env *bb, int *i)
{
	pthread_mutex_lock(&bb->mutex);
	if (!bb->someone_died && !bb->ph[*i].eating && !bb->ph[*i].must_eat
		&& (convert_time() - bb->ph[*i].last_time_eat) >= bb->time_to_die)
	{
		msg(&(bb->ph[*i]), DIED);
		bb->someone_died = 1;
		pthread_mutex_unlock(&bb->mutex);
		pthread_mutex_unlock(&bb->death);
		pthread_exit(0);
	}
	if (bb->someone_died)
	{
		pthread_mutex_unlock(&bb->mutex);
		pthread_mutex_unlock(&bb->death);
		pthread_exit(0);
	}
	(*i)++;
	if (*i >= bb->number_of_philosophers && !bb->someone_died)
		*i = 0;
	pthread_mutex_unlock(&bb->mutex);
}

void	*death(void *data)
{
	t_env	*bb;
	int i;

	bb = (t_philo *)data;
	pthread_mutex_lock(&bb->death);
	i = 0;
	while (i < bb->number_of_philosophers)
	{
		check(bb, &i);
		usleep(100);
	}
	return (0);
}

int	create_philosophers(t_env *bb)
{
	int	i;

	if (pthread_create(&(bb->death), NULL, &death, bb))
		return (-1);
	pthread_detach(bb->death);
	i = 0;
	while (i < bb->number_of_philosophers)
	{
		pthread_create(&(bb->ph[i].thread), NULL, &justdoit, &bb->ph[i]);
		i++;
	}
	i = 0;
	while (i < bb->number_of_philosophers)
	{
		pthread_join(bb->ph[i].thread, NULL);
		i++;
	}

	/* print la synthese */
	printf("to sum up !\n\n");
	printf("\033[32m%-15s %-15s %-15s %-15s\n", "philo", "eat", "sleep", "think");
	i = 0;
	while (i < bb->number_of_philosophers)
	{
		printf("%-15d %-15d %-15d %-15d\n", bb->ph[i].num, bb->ph[i].nb_time_eat, bb->ph[i].nb_time_sleep, bb->ph[i].nb_time_think);
		i++;
	}
	return (0);
}