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

void justenougheat(t_philo *ph)
{
	/* manger si must_eat le philo a assez manger*/
	pthread_mutex_lock(&ph->bb->mutex);
	if (ph->bb->notep_must_eat > 0 && 
		ph->nb_time_eat >= ph->bb->notep_must_eat)
	{
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
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
		return ;
	}
	pthread_mutex_unlock(&ph->bb->mutex);
	usleep(ph->bb->time_to_eat);
}

void	justeat(t_philo *ph)
{
	// int fork_num;

	// fork_num = (ph->num + 1) % ph->bb->nop;

	/* prendre les deux fourchettes */
	pthread_mutex_lock(ph->left_fork);
	print_message(ph, FORK_L);

	// if 1 seul philo justone(ph);
	if (ph->bb->nop == 1)
	{
		usleep(ph->bb->time_to_die);
		pthread_mutex_unlock(ph->left_fork);
		return ; 
	}
	pthread_mutex_lock(ph->right_fork);
	print_message(ph, FORK_R);

	/* manger pendant time_to_eat */
	print_message(ph, EATING);
	pthread_mutex_lock(&ph->mutex_eating);
	ph->eating = 1;
	get_time_in_usec(&ph->last_time_eat);
	pthread_mutex_unlock(&ph->mutex_eating);
	ph->nb_time_eat++;

	/* manger si must_eat le philo a assez manger*/
	justenougheat(ph);

	/* lacher les deux fourchettes */
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_lock(&ph->mutex_eating);
	ph->eating = 0;
	pthread_mutex_unlock(&ph->mutex_eating);
	print_message(ph, SLEEPING);
	// ph->nb_time_sleep++;
	usleep(ph->bb->time_to_sleep);
}

void	*justdoit(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	pthread_mutex_lock(&ph->bb->create);
	pthread_mutex_unlock(&ph->bb->create);
	if (ph->num % 2)
		usleep(ph->bb->time_to_eat);
	while (1)
	{
		justeat(ph);
		print_message(ph, THINKING);
		// ph->nb_time_think++;
		if (ph->bb->philo_died)
			return (0);
	}
	return (0);
}


