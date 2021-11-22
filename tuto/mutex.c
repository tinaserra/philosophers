/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:01:09 by vserra            #+#    #+#             */
/*   Updated: 2021/10/25 16:40:53 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// variable globale pour l'exemple (de pref a mettre dans une struct)
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void	*hello(void *data)
{
	char str[] = "Hello world!";

	int i = 0;
	pthread_mutex_lock(&mutex); // bloquer le mutex pendant que tue fais les actions ci dessous
	while (i <12)
	{
		fprintf(stderr, "%c", str[i]);
		usleep(100000);
		i++;
	}
	fprintf(stderr, "\n");
	fprintf(stderr, "end1\n");
	pthread_mutex_unlock(&mutex); // c bon tu peux debloquer
	pthread_exit(NULL);
}

void	*byebye(void *data)
{
	char str[] = "Bye bye";

	int i = 0;
	pthread_mutex_lock(&mutex);
	while (i < 7)
	{
		fprintf(stderr, "%c", str[i]);
		usleep(100000);
		i++;
	}
	fprintf(stderr, "\n");
	fprintf(stderr, "end2\n");
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int		main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, hello, "Hello !");
	pthread_create(&t2, NULL, byebye, "Bye, bye !");
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);

	return (0);
}