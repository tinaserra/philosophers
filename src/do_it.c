/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:42:05 by vserra            #+#    #+#             */
/*   Updated: 2021/11/03 17:46:24 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	take_fork(t_p *p)
// {
// 	int	fork_num;

// 	fork_num = (p->id + 1) % p->s->amount;
// 	pthread_mutex_lock(&(p->s->forks[p->id]));
// 	msg(p, TYPE_FORK);
// 	if (p->s->amount == 1)
// 	{
// 		s_usleep(p->s->time_to_die);
// 		pthread_mutex_unlock(&(p->s->forks[p->id]));
// 		pthread_exit(0);
// 	}
// 	pthread_mutex_lock(&(p->s->forks[fork_num]));
// 	msg(p, TYPE_FORK);
// }

// void	eat(t_p *p)
// {
// 	msg(p, TYPE_EAT);
// 	p->is_eating = 1;
// 	p->last_eat_time = get_time();
// 	(p->count_eat)++;
// 	pthread_mutex_lock(&(p->s->lock_m));
// 	if (p->s->eat_amount > 0 && p->count_eat >= p->s->eat_amount)
// 	{
// 		pthread_mutex_unlock(&(p->s->forks[p->id]));
// 		pthread_mutex_unlock(&(p->s->forks[(p->id + 1) % p->s->amount]));
// 		p->s->must_eat++;
// 		p->must_eat = 1;
// 		if (p->s->must_eat >= p->s->amount)
// 		{
// 			p->s->someone_died = 1;
// 			pthread_mutex_lock(&(p->s->write_m));
// 			s_putstr_fd(get_msg_type(TYPE_OVER), 1);
// 			pthread_mutex_unlock(&(p->s->write_m));
// 		}
// 		pthread_mutex_unlock(&(p->s->lock_m));
// 		pthread_exit(0);
// 	}
// 	pthread_mutex_unlock(&(p->s->lock_m));
// 	s_usleep(p->s->time_to_eat);
// }

// void	put_fork(t_p *p)
// {
// 	pthread_mutex_unlock(&(p->s->forks[p->id]));
// 	pthread_mutex_unlock(&(p->s->forks[(p->id + 1) % p->s->amount]));
// 	p->is_eating = 0;
// 	msg(p, TYPE_SLEEP);
// 	s_usleep(p->s->time_to_sleep);
// }

void	justeat(t_philo *ph)
{
	int fork_num;

	fork_num = (ph->num + 1) % ph->bb->number_of_philosophers;

	/* prendre les deux fourchettes */
	pthread_mutex_lock(&ph->bb->forks[ph->num]);
	print_message(ph, FORK_L);
	pthread_mutex_lock(&ph->bb->forks[fork_num]);
	print_message(ph, FORK_R);

	/* manger pendant time_to_eat */
	print_message(ph, EATING);
	ph->eating = 1;
	ph->last_time_eat = convert_time();
	ph->nb_time_eat++;
	if (ph->bb->number_of_times_each_philosopher_must_eat > 0)
	{
		pthread_mutex_lock(&ph->bb->debug);
		fprintf(stderr, "\033[92mphilo %d : dois-je manger ?\n", ph->num);
		pthread_mutex_unlock(&ph->bb->debug);
	}
	ft_usleep(ph->bb->time_to_eat);

	/* lacher les deux fourchettes */
	pthread_mutex_unlock(&ph->bb->forks[ph->num]);
	pthread_mutex_unlock(&ph->bb->forks[fork_num]);
	ph->eating = 0;
	print_message(ph, SLEEPING);
	ph->nb_time_sleep++;
	ft_usleep(ph->bb->time_to_sleep);

}

void	*justdoit(void *data)
{
	t_philo	*ph;

	int i = 0;

	ph = (t_philo *)data;
	if (ph->num % 2)
	{
		// pthread_mutex_lock(&ph->bb->debug);
		// fprintf(stderr, "\033[32mje suis le philo %d\n", ph->num);
		// pthread_mutex_unlock(&ph->bb->debug);
		ft_usleep(ph->bb->time_to_eat);
	}
	// pthread_mutex_lock(&ph->bb->debug);
	// fprintf(stderr, "\033[95mje suis le philo %d\n", ph->num);
	// pthread_mutex_unlock(&ph->bb->debug);
	if (ph->bb->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&ph->bb->write_m);
		fprintf(stderr, "\033[91mje suis l'elu\n");
		pthread_mutex_unlock(&ph->bb->write_m);
	}
	while (i < 2)
	{
		justeat(ph);
		print_message(ph, THINKING);
		ph->nb_time_think++;
		i++;
		// if (p->s->someone_died)
			// pthread_exit(0);
	}
	pthread_exit(0); // return ;
}


