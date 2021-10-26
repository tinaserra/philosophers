/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:32:23 by vserra            #+#    #+#             */
/*   Updated: 2021/10/26 20:33:02 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

static char g_str_error[NUMBER][256] =
{
	[ARGS] = "Error\nInvalid number of arguments\n",
	[ARG1] = "Error\nInvalid [number_of_philosophers]\n",
	[ARG2] = "Error\nInvalid [time_to_die]\n",
	[ARG3] = "Error\nInvalid [time_to_eat]\n",
	[ARG4] = "Error\nInvalid [time_to_sleep]\n",
	[ARG5] = "Error\nInvalid [number_of_times_each_philosopher_must_eat]\n",

};

#endif