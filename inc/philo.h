/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:13:46 by vserra            #+#    #+#             */
/*   Updated: 2021/11/02 15:13:05 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
#define PHILO_H

/*
** LIBRARIES ---------------------------------------------------------------- **
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
** ERRORS ------------------------------------------------------------------- **
*/

typedef enum		e_error{
	ARGS,
	ARG1,
	ARG2,
	ARG3,
	ARG4,
	ARG5,
	MALLOC,
	INIT_MUTEX,

	NUMBER
}					t_error;

/*
** STRUCTURES --------------------------------------------------------------- **
*/

typedef struct	s_philo
{
	int			num;
	pthread_t	thread;
}				t_philo;

typedef struct	s_env
{
	// pthread_t			t2;
	// pthread_t			t1;
	// pthread_mutex_t		mutex;

	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;

	pthread_mutex_t	death_m;
	pthread_t		death;

	pthread_mutex_t	write_m;
	pthread_mutex_t	lock_m;

	pthread_mutex_t	*forks;
	t_philo			*ph;
}				t_env;


/*
** PROTOTYPES --------------------------------------------------------------- **
*/

/* error.c */
int	print_error(t_env *bb, int error);

/* utils.c */
int		ft_strlen(char *s);
int		ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);

/* init_struct */
int	init_start(t_env *bb, int ac, char **av);

/* threads.c */
int	create_phisolophers(t_env *bb);

/* debug.c */
void	debug_print_args(t_env *bb);

#endif