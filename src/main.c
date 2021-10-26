/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:11:20 by vserra            #+#    #+#             */
/*   Updated: 2021/10/26 20:30:45 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_ph(t_philo *bb)
{
	int	i;

	bb->ph = malloc(sizeof(t_threads) * bb->number_of_philosophers);
	if (bb->ph == NULL)
		return (-1);
	i = 0;
	while (i < bb->number_of_philosophers)
	{
		bb->ph[i].num = i;
		i++;
	}
	return (0);
}

int	init_args(t_philo *bb, int ac, char **av)
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

int	main(int ac, char **av)
{
	t_philo	bb;

	(void)av;
	if (ac < 5 || ac > 6)
		return (print_error(&bb, ARGS));
	ft_bzero(&bb, sizeof(t_philo));
	init_args(&bb, ac, av);
	init_ph(&bb);

	return (0);
}