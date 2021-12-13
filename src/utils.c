/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:26:30 by vserra            #+#    #+#             */
/*   Updated: 2021/11/03 14:36:32 by vserra           ###   ########.fr       */
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

void	ft_putchar_fd(char c, int fd)
{
	int ret	__attribute__((unused));

	ret = write(fd, &c, STDOUT_FILENO);
}

void	ft_putstr_fd(char *s, int fd)
{
	int ret	__attribute__((unused));

	if (fd && s)
		ret = write(fd, s, ft_strlen(s));
}

void	ft_bzero(void *s, unsigned int n)
{
	unsigned int	i;
	char			*temp;

	i = 0;
	temp = (char *)s;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	power;
	int	save;

	power = 1;
	save = n;
	if (n < 0)
	{
		power = -1;
		ft_putchar_fd('-', fd);
	}
	while (n <= -10 || n >= 10)
	{
		n = n / 10;
		power = power * 10;
	}
	while (power != 0)
	{
		ft_putchar_fd((save / power) + '0', fd);
		save = save - (save / power) * power;
		power = power / 10;
	}
}
