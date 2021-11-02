/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:11:20 by vserra            #+#    #+#             */
/*   Updated: 2021/11/02 17:04:40 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time_in_ms)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

void	destroy(t_env *bb)
{
	int	i;

	if (bb->ph && bb->number_of_philosophers > 0)
	{
		i = 0;
		while (i < bb->number_of_philosophers)
		{
			pthread_mutex_destroy(&(bb->forks[i]));
			i++;
		}
		free(bb->forks);
		free(bb->ph);
		pthread_mutex_destroy(&(bb->death_m));
		pthread_mutex_destroy(&(bb->lock_m));
		pthread_mutex_destroy(&(bb->write_m));
	}
}

int	main(int ac, char **av)
{
	t_env	bb;

	if (ac < 5 || ac > 6)
		return (print_error(&bb, ARGS));
	if (init_start(&bb, ac, av) == -1)
		destroy(&bb);

	return (0);
}
