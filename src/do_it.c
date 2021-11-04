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

void	justeat(t_philo *ph)
{
	int fork_num;

	fork_num = (ph->num + 1) % ph->bb->number_of_philosophers;

	/* prendre les deux fourchettes */
	pthread_mutex_lock(&ph->bb->forks[ph->num]);
	print_message(ph, FORK_L);
	pthread_mutex_lock(&ph->bb->forks[fork_num]);
	print_message(ph, FORK_R);

	/* manger pendant time_to_eat */
	print_message(ph, EATING);
	ph->eating = 1;
	ph->last_time_eat = convert_time();
	ph->nb_time_eat++;
	if (ph->bb->number_of_times_each_philosopher_must_eat > 0)
	{
		pthread_mutex_lock(&ph->bb->debug);
		fprintf(stderr, "\033[92mphilo %d : dois-je manger ?\n", ph->num);
		pthread_mutex_unlock(&ph->bb->debug);
	}
	ft_usleep(ph->bb->time_to_eat);

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

	int i = 0;

	ph = (t_philo *)data;
	if (ph->num % 2)
		ft_usleep(ph->bb->time_to_eat);
	if (ph->bb->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&ph->bb->print);
		fprintf(stderr, "\033[91mje suis l'elu\n");
		pthread_mutex_unlock(&ph->bb->print);
	}
	while (i < 2)
	{
		justeat(ph);
		print_message(ph, THINKING);
		ph->nb_time_think++;
		i++;
		if (ph->bb->someone_died)
			return 0;
	}
	return 0;
}


