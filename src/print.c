/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaserra <tinaserra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:33:50 by vserra            #+#    #+#             */
/*   Updated: 2021/12/07 22:38:59 by tinaserra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "message.h"
#include "error.h"

// void	print_sumup(t_env *bb)
// {
// 	int i;

// 	/* print la synthese */
// 	printf("\n\nto sum up ! --------- *\n\n");
// 	printf("\033[32m%-15s %-15s %-15s %-15s\n", "philo", "eat", "sleep", "think");
// 	i = 0;
// 	while (i < bb->nop)
// 	{
// 		printf("%-15d %-15d %-15d %-15d\n", bb->ph[i].num, bb->ph[i].nb_time_eat, bb->ph[i].nb_time_sleep, bb->ph[i].nb_time_think);
// 		i++;
// 	}
// }

// int	print_message(t_philo *ph, int msg)
// {
// 	useconds_t time;

// 	pthread_mutex_lock(&ph->bb->print);
// 	pthread_mutex_lock(&ph->bb->died);
// 	if (ph->bb->philo_died)
// 	{
// 		pthread_mutex_unlock(&ph->bb->print);
// 		pthread_mutex_unlock(&ph->bb->died);
// 		return (0);
// 	}
// 	// ft_putstr_fd("time : ", STDOUT_FILENO);
// 	get_time_in_usec(&time);

// 	ft_putnbr_fd((time - ph->bb->start_time) / 1000, STDOUT_FILENO);
// 	ft_putstr_fd(" ", STDOUT_FILENO);
// 	ft_putnbr_fd((ph->num + 1), STDOUT_FILENO);
// 	// ft_putstr_fd(" : ", STDOUT_FILENO);
// 	ft_putstr_fd(g_str_msg[msg], STDOUT_FILENO);
// 	pthread_mutex_unlock(&ph->bb->died);
// 	pthread_mutex_unlock(&ph->bb->print);
// 	return (0);
// }

int	print_message(t_philo *ph, int msg)
{
	useconds_t time;

	pthread_mutex_lock(&ph->bb->print);
	pthread_mutex_lock(&ph->bb->died);
	if (ph->bb->philo_died)
	{
		pthread_mutex_unlock(&ph->bb->print);
		pthread_mutex_unlock(&ph->bb->died);
		return (0);
	}
	// ft_putstr_fd("time : ", STDOUT_FILENO);
	get_time_in_usec(&time);

	printf("%d %d%s", (time - ph->bb->start_time) / 1000, ph->num + 1, g_str_msg[msg]);

	pthread_mutex_unlock(&ph->bb->died);
	pthread_mutex_unlock(&ph->bb->print);
	return (0);
}

int	print_error(int error)
{
	ft_putstr_fd(g_str_error[error], STDERR_FILENO);
	return (-1);
}
