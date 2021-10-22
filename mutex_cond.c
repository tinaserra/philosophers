/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_cond.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:01:09 by vserra            #+#    #+#             */
/*   Updated: 2021/10/22 19:24:27 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// variable globale pour l'exemple (de pref a mettredans une struct)
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void	*hello1(void *data)
{
	char str[] = "hello world!";
	int i = 0;
	pthread_cond_wait(&cond, &mutex); // le thread attend la condition pour se lancer
	while (i <12)
	{
		fprintf(stderr, "%c", str[i]);
		usleep(100000);
		i++;
	}
	fprintf(stderr, "\n");

	fprintf(stderr, "end1\n");
	pthread_exit(NULL);
}

void	*hello2(void *data)
{
	char str[] = "Bye bye";
	int i = 0;
	while (i < 7)
	{
		fprintf(stderr, "%c", str[i]);
		usleep(100000);
		i++;
	}
	fprintf(stderr, "\n");

	fprintf(stderr, "end2\n");
	pthread_cond_signal(&cond); // on envoi la condition au thread 1
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