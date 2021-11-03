/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:01:09 by vserra            #+#    #+#             */
/*   Updated: 2021/11/03 17:23:45 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct	s_philo
{
	pthread_t		t1;
	pthread_t		t2;
	pthread_mutex_t	mutex;
}				t_philo;

void	*ciao(void *data)
{
	t_philo *philo;
	char *s1;

	philo = (t_philo *)data;
	int i = 0;
	s1 = "Ciao ciao !";
	pthread_mutex_lock(&philo->mutex); // bloquer le mutex pendant que tue fais les actions ci dessous
	while (i < 11)
	{
		fprintf(stderr, "%c", s1[i]);
		usleep(100000);
		i++;
	}
	fprintf(stderr, "\n");
	fprintf(stderr, "end1\n");
	pthread_mutex_unlock(&philo->mutex); // c bon tu peux debloquer
	pthread_exit(NULL);
}

void	*bye(void *data)
{
	t_philo *philo;
	char *s2;

	philo = (t_philo *)data;
	int i = 0;
	s2 = "Bye bye";
	pthread_mutex_lock(&philo->mutex);
	while (i < 7)
	{
		fprintf(stderr, "%c", s2[i]);
		usleep(100000);
		i++;
	}
	fprintf(stderr, "\n");
	fprintf(stderr, "end2\n");
	pthread_mutex_unlock(&philo->mutex);
	pthread_exit(NULL);
}

void	create_threads(t_philo *philo)
{
	pthread_create(&philo->t1, NULL, ciao, philo);
	pthread_create(&philo->t2, NULL, bye, philo);
}

int		main(void)
{
	t_philo	philo;
	
	pthread_mutex_init(&philo.mutex, NULL); // obligatoire de init le mutex
	
	create_threads(&philo);
	// pthread_create(&philo.t1, NULL, hello1, &philo);
	// pthread_create(&philo.t2, NULL, hello2, &philo);
	pthread_join(philo.t1, NULL);
	pthread_join(philo.t2, NULL);

	pthread_mutex_destroy(&philo.mutex);
	return (0);
}