/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_it.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaserra <tinaserra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:42:05 by vserra            #+#    #+#             */
/*   Updated: 2022/01/07 09:26:32 by tinaserra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** if 1 seul philo justone(ph);
*/

static int	justone(t_philo *ph)
{
	if (ph->bb->nop == 1)
	{
		ft_usleep(ph->bb->time_to_die, ph->bb);
		pthread_mutex_unlock(ph->left_fork);
		return (-1);
	}
	pthread_mutex_lock(ph->right_fork);
	print_message(ph, FORK_R);
	return (0);
}

/*
** prendre les deux fourchettes
** manger pendant time_to_eat
** lacher les deux fourchettes
*/

static void	justeat(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	print_message(ph, FORK_L);
	if (justone(ph) == -1)
		return ;
	// print_message(ph, EATING);
	pthread_mutex_lock(&ph->mutex_eating);
	print_message(ph, EATING);
	ph->eating = 1;
	get_time_in_usec(&ph->last_time_eat);
	pthread_mutex_unlock(&ph->mutex_eating);
	ft_usleep(ph->bb->time_to_eat, ph->bb);
	pthread_mutex_lock(&ph->mutex_eating);
	ph->nb_time_eat++;
	pthread_mutex_unlock(&ph->mutex_eating);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_lock(&ph->mutex_eating);
	ph->eating = 0;
	pthread_mutex_unlock(&ph->mutex_eating);
	print_message(ph, SLEEPING);
	ft_usleep(ph->bb->time_to_sleep, ph->bb);
}

void	*justdoit(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	pthread_mutex_lock(&ph->bb->create);
	pthread_mutex_unlock(&ph->bb->create);
	if (ph->num % 2)
		ft_usleep(ph->bb->time_to_eat, ph->bb);
	while (1)
	{
		justeat(ph);
		print_message(ph, THINKING);
		pthread_mutex_lock(&ph->bb->died);
		if (ph->bb->philo_died)
		{
			pthread_mutex_unlock(&ph->bb->died);
			return (0);
		}
		pthread_mutex_unlock(&ph->bb->died);
	}
	return (0);
}
