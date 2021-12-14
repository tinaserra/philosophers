/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:33:50 by vserra            #+#    #+#             */
/*   Updated: 2021/12/14 16:37:20 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "message.h"
#include "error.h"

int	print_message(t_philo *ph, int msg)
{
	useconds_t	time;

	pthread_mutex_lock(&ph->bb->print);
	pthread_mutex_lock(&ph->bb->died);
	if (ph->bb->philo_died)
	{
		pthread_mutex_unlock(&ph->bb->print);
		pthread_mutex_unlock(&ph->bb->died);
		return (0);
	}
	get_time_in_usec(&time);
	printf("%d %d%s", (time - ph->bb->start_time) / 1000,
		ph->num + 1, g_str_msg[msg]);
	pthread_mutex_unlock(&ph->bb->died);
	pthread_mutex_unlock(&ph->bb->print);
	return (0);
}

int	print_error(int error)
{
	ft_putstr_fd(g_str_error[error], STDERR_FILENO);
	return (-1);
}
