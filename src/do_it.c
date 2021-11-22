/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:42:05 by vserra            #+#    #+#             */
/*   Updated: 2021/11/03 17:46:24 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void justenougheat(t_philo *ph, int fork_num)
{
	/* manger si must_eat le philo a assez manger*/
	pthread_mutex_lock(&ph->bb->mutex);
	if (ph->bb->number_of_times_each_philosopher_must_eat > 0 && 
		ph->nb_time_eat >= ph->bb->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_unlock(&ph->bb->forks[ph->num]);
		pthread_mutex_unlock(&ph->bb->forks[fork_num]);
		ph->bb->enough_eat++; // un philo a mange asser
		ph->enough_eat = 1; // le philo a asser manger
		if (ph->bb->enough_eat >= ph->bb->number_of_philosophers)
		{
			ph->bb->someone_died = 1;
			pthread_mutex_lock(&(ph->bb->print));
			print_message(ph, DIED);
			pthread_mutex_unlock(&(ph->bb->print));
		}
		pthread_mutex_unlock(&ph->bb->mutex);
		return ;
		// pthread_exit(0);
	}
	pthread_mutex_unlock(&ph->bb->mutex);
	ft_usleep(ph->bb->time_to_eat);
}

void	justeat(t_philo *ph)
{
	int fork_num;

	fork_num = (ph->num + 1) % ph->bb->number_of_philosophers;

	/* prendre les deux fourchettes */
	pthread_mutex_lock(&ph->bb->forks[ph->num]);
	print_message(ph, FORK_L);
	// if 1 seul philo
	pthread_mutex_lock(&ph->bb->forks[fork_num]);
	print_message(ph, FORK_R);

	/* manger pendant time_to_eat */
	print_message(ph, EATING);
	ph->eating = 1;
	ph->last_time_eat = convert_time();
	ph->nb_time_eat++;

	/* manger si must_eat le philo a assez manger*/
	justenougheat(ph, fork_num);

	/* lacher les deux fourchettes */
	pthread_mutex_unlock(&ph->bb->forks[ph->num]);
	pthread_mutex_unlock(&ph->bb->forks[fork_num]);
	ph->eating = 0;
	print_message(ph, SLEEPING);
	ph->nb_time_sleep++;
	ft_usleep(ph->bb->time_to_sleep);
}

void	*justdoit(void *data)
{
	t_philo	*ph;

	// int i = 0;

	ph = (t_philo *)data;
	if (ph->num % 2)
		ft_usleep(ph->bb->time_to_eat);
	// if (ph->bb->number_of_philosophers == 1)
	// {
	// 	pthread_mutex_lock(&ph->bb->print);
	// 	fprintf(stderr, "\033[91mje suis l'elu\n");
	// 	pthread_mutex_unlock(&ph->bb->print);
	// }
	while (1)
	{
		justeat(ph);
		print_message(ph, THINKING);
		ph->nb_time_think++;
		// i++;
		if (ph->bb->someone_died)
			return (0);
			// pthread_exit(0);
	}
	return (0);
	// pthread_exit(0);
}


