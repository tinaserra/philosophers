#include "philo.h"

int	time_atoi(const char *str, useconds_t *time)
{
	int	i;
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
	*time = nbr;
	return (0);
}

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