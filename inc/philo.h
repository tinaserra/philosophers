/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaserra <tinaserra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:13:46 by vserra            #+#    #+#             */
/*   Updated: 2021/11/04 09:56:49 by tinaserra        ###   ########.fr       */
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
# include <string.h>
# include <sys/time.h>

/*
** MESSAGES ----------------------------------------------------------------- **
*/

typedef enum		e_msg{
	EATING,
	SLEEPING,
	THINKING,
	FORK_L,
	FORK_R,
	DIED,
	ALL,

	TOTAL
}					t_msg;

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
	GETTIMEOFDAY,

	NUMBER
}					t_error;

/*
** STRUCTURES --------------------------------------------------------------- **
*/

typedef struct	s_philo
{
	int			num;
	int			eating;
	int			enough_eat;
	int			nb_time_eat;
	int			nb_time_sleep;
	int			nb_time_think;
	unsigned int last_time_eat;
	pthread_t	thread;

	struct s_env	*bb;
}				t_philo;

typedef struct	s_env
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;

	int				someone_died;
	int				enough_eat;
	long			start_time;

	pthread_t		death;

	pthread_mutex_t	debug;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex;

	pthread_mutex_t	*forks;
	t_philo			*ph;
}				t_env;


/*
** PROTOTYPES --------------------------------------------------------------- **
*/

/* string.c */
int	print_error(int error);
int	print_message(t_philo *ph, int msg);

/* utils.c */
int		ft_strlen(char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
unsigned int	convert_time(void);
void	ft_usleep(unsigned int time_in_ms);

/* init_struct */
int	init_start(t_env *bb, int ac, char **av);

/* threads.c */
int	create_philosophers(t_env *bb);

/* states.c */
void	*justdoit(void *data);

/* debug.c */
void	debug_print_args(t_env *bb);

#endif