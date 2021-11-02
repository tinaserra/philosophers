/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:08:41 by vserra            #+#    #+#             */
/*   Updated: 2021/11/02 17:42:49 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_phisolophers(t_env *bb)
{
	int	i;

	// if (pthread_create(&(bb->death), NULL, &death, bb))
	// 	return (-1);
	// pthread_detach(bb->death);
	i = -1;
	while (++i < bb->number_of_philosophers)
	{
		if (pthread_create(&(bb->ph[i].thread), NULL, &justdoit, &(bb->ph[i])))
			return (0);
	}
	i = -1;
	while (++i < bb->number_of_philosophers)
		if (pthread_join(bb->ph[i].thread, NULL))
			return (0);
	return (1);
}