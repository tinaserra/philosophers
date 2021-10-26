/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:11:20 by vserra            #+#    #+#             */
/*   Updated: 2021/10/26 16:10:32 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_philo *bb, int ac, char **av)
{
	bb->number_of_philosophers = ft_atoi(av[1]);
	bb->time_to_die = ft_atoi(av[2]);
	bb->time_to_eat = ft_atoi(av[3]);
	bb->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		bb->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	debug_print_args(bb);
}

int	main(int ac, char **av)
{
	t_philo	bb;

	(void)av;
	if (ac < 5 || ac > 6)
		return (print_error(&bb, ARGS));
	init_args(&bb, ac, av);

	return (0);
}