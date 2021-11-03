/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:11:20 by vserra            #+#    #+#             */
/*   Updated: 2021/11/03 15:43:21 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time(void)
{
	static struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
		return (print_error(ARGS));
	if (init_start(&bb, ac, av) == -1)
		destroy(&bb);
	create_philosophers(&bb);

	// pthread_mutex_lock(&(s.death_m));
	// pthread_mutex_unlock(&(s.death_m));
	ft_usleep(5);
	destroy(&bb);

	return (0);
}
