/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_it.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaserra <tinaserra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:42:05 by vserra            #+#    #+#             */
/*   Updated: 2021/12/07 22:46:10 by tinaserra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void justenougheat(t_philo *ph, int fork_num)
{
	(void)fork_num;
	/* manger si must_eat le philo a assez manger*/
	pthread_mutex_lock(&ph->bb->mutex);
	if (ph->bb->notep_must_eat > 0 && 
		ph->nb_time_eat >= ph->bb->notep_must_eat)
	{
		pthread_mutex_unlock(&ph->bb->forks[ph->num]);
		pthread_mutex_unlock(&ph->bb->forks[(ph->num + 1) % ph->bb->nop]);
		ph->bb->enough_eat++; // un philo a mange asser
		ph->enough_eat = 1; // le philo a asser manger
		if (ph->bb->enough_eat >= ph->bb->nop)
		{
			ph->bb->philo_died = 1;
			pthread_mutex_lock(&(ph->bb->print));
			print_message(ph, DIED);
			pthread_mutex_unlock(&(ph->bb->print));
		}
		pthread_mutex_unlock(&ph->bb->mutex);
		pthread_exit(0);
	}
	pthread_mutex_unlock(&ph->bb->mutex);
	usleep(ph->bb->time_to_eat);
}

void	justeat(t_philo *ph)
{
	int fork_num;

	fork_num = (ph->num + 1) % ph->bb->nop;

	/* prendre les deux fourchettes */
	pthread_mutex_lock(&ph->bb->forks[ph->num]);
	print_message(ph, FORK_L);

	// if 1 seul philo justone(ph);
	if (ph->bb->nop == 1)
	{
		usleep(ph->bb->time_to_die);
		pthread_mutex_unlock(&ph->bb->forks[ph->num]);
		return ; 
	}
	pthread_mutex_lock(&ph->bb->forks[fork_num]);
	print_message(ph, FORK_R);

	/* manger pendant time_to_eat */
	print_message(ph, EATING);
	ph->eating = 1;
	get_time_in_usec(&ph->last_time_eat);
	ph->nb_time_eat++;
	pthread_mutex_unlock(&ph->bb->mutex); // ---------------

	/* manger si must_eat le philo a assez manger*/
	justenougheat(ph, fork_num);

	/* lacher les deux fourchettes */
	pthread_mutex_unlock(&ph->bb->forks[ph->num]);
	pthread_mutex_unlock(&ph->bb->forks[fork_num]);
	ph->eating = 0;
	print_message(ph, SLEEPING);
	ph->nb_time_sleep++;
	usleep(ph->bb->time_to_sleep);
}

void	*justdoit(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	if (ph->num % 2)
		usleep(ph->bb->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(&ph->bb->mutex); // --------------
		justeat(ph);

		print_message(ph, THINKING);
		ph->nb_time_think++;
		if (ph->bb->philo_died)
			return (0);
	}
	return (0);
}


