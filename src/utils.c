/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:26:30 by vserra            #+#    #+#             */
/*   Updated: 2021/10/26 16:12:01 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (fd && s)
	{
		write(fd, s, ft_strlen(s));
		return (ft_strlen(s));
	}
	return (0);
}

int	ft_atoi(const char *str)
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
	return (nbr);
}
