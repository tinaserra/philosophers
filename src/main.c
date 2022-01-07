/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaserra <tinaserra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:11:20 by vserra            #+#    #+#             */
/*   Updated: 2022/01/07 09:39:27 by tinaserra        ###   ########.fr       */
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

long int	get_time_in_usec(useconds_t *actual_time)
{
	static struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (print_error(GETTIMEOFDAY));
	*actual_time = ((current_time.tv_sec * 1000000) + (current_time.tv_usec));
	return (*actual_time);
}

long int	get_time_in_usec_to_print(useconds_t start_time)
{
	static struct timeval	current_time;
	useconds_t				actual_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (print_error(GETTIMEOFDAY));
	actual_time = ((current_time.tv_sec * 1000000) + (current_time.tv_usec));
	actual_time -= start_time;
	return (actual_time);
}

/*
** la vraie fonction usleep attend au minimum le temps qu'on lui indique
** donc n'est pas precise
*/

int	ft_usleep(useconds_t time_in_usec, t_env *bb)
{
	useconds_t	start_time;
	useconds_t	actual_time;

	start_time = 0;
	actual_time = 0;
	if (get_time_in_usec(&start_time) == -1)
		return (-1);
	while ((get_time_in_usec(&actual_time) - start_time) < time_in_usec)
	{
		pthread_mutex_lock(&bb->died);
		if (bb->philo_died)
		{
			pthread_mutex_unlock(&bb->died);
			break ;
		}
		pthread_mutex_unlock(&bb->died);
		usleep(500);
	}
	return (0);
}

void	destroy(t_env *bb)
{
	// int	i;

	if (bb->ph && bb->nop > 0)
	{
		// i = 0;
		// while (i < bb->nop)
		// {
		// 	pthread_mutex_destroy(&bb->ph[i].mutex_eating);
		// 	pthread_mutex_destroy(&bb->ph[i].fork);
		// 	i++;
		// }
		free(bb->ph);
		// pthread_mutex_destroy(&bb->death);
		// pthread_mutex_destroy(&bb->mutex);
		// pthread_mutex_destroy(&bb->print);
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
		return (-1);
	}
	if (create_philosophers(&bb) == -1)
	{
		destroy(&bb);
		return (-1);
	}
	usleep(5);
	destroy(&bb);
	return (0);
}
