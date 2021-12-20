/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:26:31 by vserra            #+#    #+#             */
/*   Updated: 2021/12/20 15:36:34 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_env *bb)
{
	if (pthread_mutex_init(&(bb->print), NULL))
		return (-1);
	if (pthread_mutex_init(&(bb->mutex), NULL))
		return (-1);
	if (pthread_mutex_init(&(bb->death), NULL))
		return (-1);
	if (pthread_mutex_init(&(bb->debug), NULL))
		return (-1);
	if (pthread_mutex_init(&(bb->create), NULL))
		return (-1);
	if (pthread_mutex_init(&(bb->died), NULL))
		return (-1);
	return (0);
}

// static int	init_forks(t_env *bb, int i)
// {
// 	if (pthread_mutex_init(&(bb->ph[i].fork), NULL))
// 		return (-1);
// 	bb->ph[i].right_fork = &bb->ph[(i + 1) % bb->nop].fork;
// 	bb->ph[i].left_fork = &bb->ph[i].fork;
// 	if (i == bb->nop - 1)
// 	{
// 		bb->ph[i].right_fork = &bb->ph[i].fork;
// 		bb->ph[i].left_fork = &bb->ph[(i + 1) % bb->nop].fork;
// 	}
// 	if (pthread_mutex_init(&(bb->ph[i].mutex_eating), NULL))
// 		return (-1);
// 	return (0);
// }

static int	init_struct(t_env *bb)
{
	int	i;

	bb->ph = malloc(sizeof(t_philo) * bb->nop);
	if (bb->ph == NULL)
		return (print_error(MALLOC));
	i = 0;
	while (i < bb->nop)
	{
		bb->ph[i].num = i;
		bb->ph[i].bb = bb;
		bb->ph[i].eating = 0;
		bb->ph[i].nb_time_eat = 0;
		bb->ph[i].enough_eat = 0;
		get_time_in_usec(&bb->ph[i].last_time_eat);
		// if (init_forks(bb, i) == -1)
		// 	return (print_error(INIT_FORKS));

		if (pthread_mutex_init(&(bb->ph[i].fork), NULL))
			return (-1);
		bb->ph[i].right_fork = &bb->ph[(i + 1) % bb->nop].fork;
		bb->ph[i].left_fork = &bb->ph[i].fork;
		// if (i == bb->nop - 1)
		// {
		// 	bb->ph[i].right_fork = &bb->ph[i].fork;
		// 	bb->ph[i].left_fork = &bb->ph[(i + 1) % bb->nop].fork;
		// }
		if (pthread_mutex_init(&(bb->ph[i].mutex_eating), NULL))
			return (-1);
		i++;
	}
	return (0);
}

/*
p1 fL
p2 fL 
p3 fL
p4 fL
p5 fL
*/

static int	init_args(t_env *bb, int ac, char **av)
{
	if (nbr_atoi(av[1], &bb->nop) == -1)
		return (print_error(ARG1));
	if (time_atoi(av[2], &bb->time_to_die) == -1)
		return (print_error(ARG2));
	if (time_atoi(av[3], &bb->time_to_eat) == -1)
		return (print_error(ARG3));
	if (time_atoi(av[4], &bb->time_to_sleep) == -1)
		return (print_error(ARG4));
	if (ac == 6)
		if (nbr_atoi(av[5], &bb->notep_must_eat) == -1)
			return (print_error(ARG5));
	get_time_in_usec(&bb->start_time);
	debug_print_args(bb);
	debug_print_struct(bb);
	return (0);
}

int	init_start(t_env *bb, int ac, char **av)
{
	ft_bzero(bb, sizeof(t_env));
	if (init_args(bb, ac, av) == -1)
		return (-1);
	if (init_struct(bb) == -1)
		return (-1);
	if (init_mutex(bb) == -1)
		return (print_error(INIT_MUTEX));
	return (0);
}
