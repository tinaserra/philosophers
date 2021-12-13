/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaserra <tinaserra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:11:20 by vserra            #+#    #+#             */
/*   Updated: 2021/12/07 22:31:39 by tinaserra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int		g_time_now;

/*
** int gettimeofday(struct timeval *tv, struct timezone *tz);
**
** L'utilisation de la structure timezone est obsolète
** le fuseau horraire n'est pas gere sous linux. 
** l'argument timezone doit etre NULL.
*/

int	get_time_in_usec(useconds_t *actual_time)
{
	static struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (print_error(GETTIMEOFDAY));
	*actual_time = ((current_time.tv_sec * 1000000) + (current_time.tv_usec));
	return (0);
}

/*
** la vraie fonction usleep attend au minimum le temps qu'on lui indique
** donc n'est pas precise
*/

// int	ft_usleep(useconds_t time_in_ms)
// {
// 	useconds_t	start_time;

// 	if (get_time_in_usec(&start_time) == -1)
// 		return (print_error(GETTIMEOFDAY));
// 	while ((get_time_in_usec(&start_time) - start_time) < time_in_ms)
// 		usleep(time_in_ms / 10);
// 	return (0);
// }

void	destroy(t_env *bb)
{
	int	i;

	if (bb->ph && bb->nop > 0)
	{
		i = 0;
		while (i < bb->nop)
		{
			pthread_mutex_destroy(&bb->ph[i].mutex_eating);
			pthread_mutex_destroy(&bb->ph[i].fork);
			// bb->ph[i].right_fork = NULL;
			i++;
		}
		free(bb->ph);
		pthread_mutex_destroy(&bb->death);
		pthread_mutex_destroy(&bb->mutex);
		pthread_mutex_destroy(&bb->print);
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
	if (create_philosophers(&bb) == -1)
	{
		destroy(&bb);
		return (-1);
	}
	// death(&bb);
	// pthread_mutex_lock(&bb.death);
	// pthread_mutex_unlock(&bb.death);
	usleep(5);
	destroy(&bb);
	return (0);
}
