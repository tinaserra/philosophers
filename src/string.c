/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:33:50 by vserra            #+#    #+#             */
/*   Updated: 2021/11/03 14:36:04 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "message.h"
#include "error.h"

int	print_message(t_philo *ph, int msg)
{
	pthread_mutex_lock(&(ph->bb->write_m));
	if (ph->bb->someone_died)
	{
		pthread_mutex_unlock(&(ph->bb->write_m));
		return (0);
	}
	ft_putnbr_fd(get_time() - ph->bb->start_time, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putnbr_fd((ph->num + 1), STDOUT_FILENO);
	ft_putstr_fd(g_str_msg[msg], STDOUT_FILENO);
	pthread_mutex_unlock(&(ph->bb->write_m));
	return (0);
}

int	print_error(int error)
{
	ft_putstr_fd(g_str_error[error], STDERR_FILENO);
	return (-1);
}
