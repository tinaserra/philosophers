/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:42:05 by vserra            #+#    #+#             */
/*   Updated: 2021/11/02 18:00:56 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*justdoit(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	// if (ph->num % 2)
	// 	ft_usleep(ph->bb->time_to_eat);
	while (1)
	{
		printf("pute pute pute\n");
		// take_fork(p);
		// eat(p);
		// put_fork(p);
		// msg(p, TYPE_THINK);
		// if (p->s->someone_died)
		// 	pthread_exit(0);
	}
	pthread_exit(0);
}