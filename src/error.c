/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:33:50 by vserra            #+#    #+#             */
/*   Updated: 2021/11/03 13:02:21 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "error.h"

int	print_error(int error)
{
	ft_putstr_fd(g_str_error[error], STDERR_FILENO);
	return (-1);
}
