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

int	create_philosophers(t_env *bb)
{
	int	i;

	// if (pthread_create(&(bb->death), NULL, &death, bb))
	// 	return (-1);
	// pthread_detach(bb->death);
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
	return (0);
}