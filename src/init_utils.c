/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:35:08 by vserra            #+#    #+#             */
/*   Updated: 2021/12/14 16:35:48 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_atoi(const char *str, useconds_t *time)
{
	int			i;
	useconds_t	nbr;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	i = 0;
	nbr = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10);
		nbr = nbr + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	*time = nbr * 1000;
	return (0);
}

// checker over flow pour time to sleep

int	nbr_atoi(const char *str, int *arg)
{
	int	i;
	int	nbr;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	i = 0;
	nbr = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10);
		nbr = nbr + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	*arg = nbr;
	return (0);
}
