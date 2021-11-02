/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:26:31 by vserra            #+#    #+#             */
/*   Updated: 2021/11/02 14:50:32 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_env *bb)
{
	// int	i;

	if (pthread_mutex_init(&(bb->write_m), NULL))
		return (-1);
	if (pthread_mutex_init(&(bb->lock_m), NULL))
		return (-1);
	if (pthread_mutex_init(&(bb->death_m), NULL))
		return (-1);
	// i = 0;
	// while (i < bb->number_of_philosophers)
	// {
	// 	if (pthread_mutex_init(&(bb->forks[i]), NULL))
	// 		return (0);
	// 	i++;
	// }
	return (0);
}

static int	init_struct(t_env *bb)
{
	int	i;

	bb->ph = malloc(sizeof(t_philo) * bb->number_of_philosophers);
	if (bb->ph == NULL)
		return (-1);
	bb->forks = malloc(sizeof(pthread_mutex_t) * bb->number_of_philosophers);
	if (bb->forks == NULL)
		return (-1);
	i = 0;
	while (i < bb->number_of_philosophers)
	{
		bb->ph[i].num = i;
		if (pthread_mutex_init(&(bb->forks[i]), NULL))
			return (-1);
		i++;
	}
	return (0);
}

static int	init_args(t_env *bb, int ac, char **av)
{
	bb->number_of_philosophers = ft_atoi(av[1]);
	if (bb->number_of_philosophers == -1)
		return (print_error(bb, ARG1));
	bb->time_to_die = ft_atoi(av[2]);
	if (bb->time_to_die == -1)
		return (print_error(bb, ARG2));
	bb->time_to_eat = ft_atoi(av[3]);
	if (bb->time_to_eat == -1)
		return (print_error(bb, ARG3));
	bb->time_to_sleep = ft_atoi(av[4]);
	if (bb->time_to_sleep == -1)
		return (print_error(bb, ARG4));
	if (ac == 6)
		bb->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	if (bb->number_of_times_each_philosopher_must_eat == -1)
		return (print_error(bb, ARG5));
	debug_print_args(bb);
	return (0);
}

int	init_start(t_env *bb, int ac, char **av)
{
	ft_bzero(bb, sizeof(t_env));
	if (init_args(bb, ac, av) == -1)
		return (-1);
	if (init_struct(bb) == -1)
		return (print_error(bb, MALLOC));
	if (init_mutex(bb) == -1)
		return (print_error(bb, INIT_MUTEX));
	return (0);
}