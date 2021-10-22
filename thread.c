/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:51:51 by vserra            #+#    #+#             */
/*   Updated: 2021/10/22 18:00:35 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void	*funct1(void *arg)
{
	int i;
	i = 0;

	while(i < 10)
	{
		fprintf(stderr, "\033[91mthread 1: %s\033[0m\n", (char*)arg);
		i++;
	}
	pthread_exit(arg);
}

void	*funct2(void *arg)
{
	int i;
	i = 0;

	while(i < 10)
	{
		fprintf(stderr, "\033[95mthread 2: %s\033[0m\n", (char*)arg);
		i++;
	}
	pthread_exit(arg);
}

int		main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, funct1, "Hello !");
	pthread_create(&t2, NULL, funct2, "Bye, bye !");

	char *s1, *s2;
	pthread_join(t1, (void**)&s1);
	pthread_join(t2, (void**)&s2);
	printf("%s %s\n", s1, s2);

	return (0);
}