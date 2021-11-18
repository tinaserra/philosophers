/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:34:53 by vserra            #+#    #+#             */
/*   Updated: 2021/11/02 14:06:03 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#ifdef DEBUG

void	debug_print_args(t_env *bb)
{
	printf("\n\n* DEBUG PRINT ARGS ----------- *\n\n");
	printf("nb philo = %d\n", bb->number_of_philosophers);
	printf("time_to_die = %d\n", bb->time_to_die);
	printf("time_to_eat = %d\n", bb->time_to_eat);
	printf("time_to_sleep = %d\n\n", bb->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat = %d\n\n", bb->number_of_times_each_philosopher_must_eat);
}

#else

void	debug_print_args(t_env *bb)
{
	(void)bb;
	return ;
}

#endif

#ifdef DEBUG

void	debug_print_struct(t_env *bb)
{
	printf("\n\n* DEBUG PRINT STRUCT ---------- *\n\n");
	printf("nb philo = %d\n", bb->someone_died);
	printf("time_to_die = %d\n", bb->enough_eat);
	printf("time_to_eat = %d\n", bb->start_time);
}

#else

void	debug_print_struct(t_env *bb)
{
	(void)bb;
	return ;
}

#endif