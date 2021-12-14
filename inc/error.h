/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:24:31 by vserra            #+#    #+#             */
/*   Updated: 2021/11/03 14:25:24 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

static char g_str_error[NUMBER][256] =
{
	[ARGS] = "Error\nInvalid number of arguments\n",
	[ARG1] = "Error\nInvalid [nop]\n",
	[ARG2] = "Error\nInvalid [time_to_die]\n",
	[ARG3] = "Error\nInvalid [time_to_eat]\n",
	[ARG4] = "Error\nInvalid [time_to_sleep]\n",
	[ARG5] = "Error\nInvalid [notep_must_eat]\n",
	[MALLOC] = "Error\nMemory allocation failed\n",
	[INIT_FORKS] = "Error\nInit forks",
	[INIT_MUTEX] = "Error\nInit mutex\n",
	[GETTIMEOFDAY] = "Error\ngettimeofday() failed",

};

#endif