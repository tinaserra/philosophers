/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:01:09 by vserra            #+#    #+#             */
/*   Updated: 2021/10/22 18:48:53 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void	*hello1(void *data)
{
	// int *value = &((mutex*)data)->val;
	char str[] = "hello world!";
	int i = 0;
	while (i <12)
	{
		pthread_mutex_lock(&mutex); //bloquer le mutex pendant que tue fais les actions ci dessous
		fprintf(stderr, "%c", str[i]);
		usleep(100000);
		pthread_mutex_unlock(&mutex); // c bon tu peux debloquer
		i++;
	}
	fprintf(stderr, "\n");

	fprintf(stderr, "end1\n");
	pthread_exit(NULL);
}

void	*hello2(void *data)
{
	// int *value = &((mutex*)data)->val;
	char str[] = "Bye bye";
	int i = 0;
	while (i <7)
	{
		pthread_mutex_lock(&mutex);
		fprintf(stderr, "%c", str[i]);
		usleep(100000);
		pthread_mutex_unlock(&mutex);
		i++;
	}
	fprintf(stderr, "\n");

	fprintf(stderr, "end2\n");
	pthread_exit(NULL);
}

int		main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, hello1, "Hello !");
	pthread_create(&t2, NULL, hello2, "Bye, bye !");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return (0);
}