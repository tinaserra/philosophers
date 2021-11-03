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


void	*justdoit(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	pthread_mutex_lock(&ph->bb->write_m);
	
	fprintf(stderr, "\033[95mje suis le philo %d\n", ph->num);
	fprintf(stderr, "\033[95mpute\n");

	// print_message(ph, EATING);
	// usleep(10000000);

	pthread_mutex_unlock(&ph->bb->write_m);
	pthread_exit(0);
}



	// if (ph->num % 2)
	// 	ft_usleep(ph->bb->time_to_eat);
	// while (1)
	// {
		// printf("pute pute pute\n");
		// take_fork(p);
		// eat(p);
		// put_fork(p);
		// msg(p, TYPE_THINK);
		// if (p->s->someone_died)
		// 	pthread_exit(0);
	// }