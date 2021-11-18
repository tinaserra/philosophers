/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaserra <tinaserra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:11:20 by vserra            #+#    #+#             */
/*   Updated: 2021/11/04 10:01:51 by tinaserra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** int gettimeofday(struct timeval *tv, struct timezone *tz);
**
** L'utilisation de la structure timezone est obsolète
** le fuseau horraire n'est pas gere sous linux. 
** l'argument timezone doit etre NULL.
*/

int	convert_time(void)
{
	static struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (print_error(GETTIMEOFDAY));
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

/*
** la vraie fonction usleep attend au minimum le temps qu'on lui indique
** donc n'est pas precise
*/

void	ft_usleep(useconds_t time_in_ms)
{
	useconds_t	start_time;

	start_time = convert_time();
	while ((convert_time() - start_time) < time_in_ms)
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
		pthread_mutex_destroy(&(bb->death));
		pthread_mutex_destroy(&(bb->mutex));
		pthread_mutex_destroy(&(bb->print));
	}
}

int	main(int ac, char **av)
{
	t_env	bb;

	if (ac < 5 || ac > 6)
		return (print_error(ARGS));
	if (init_start(&bb, ac, av) == -1)
	{
		destroy(&bb);
		debug_print_args(&bb);
		return (-1);
	}
	create_philosophers(&bb);

	// pthread_mutex_lock(&bb.death);
	// pthread_mutex_unlock(&bb.death);
	ft_usleep(5);
	destroy(&bb);

	return (0);
}
