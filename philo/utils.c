/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:18:29 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/07 17:26:42 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *message)
{
	printf(RED"error - ");
	printf(RST"%s", message);
}

static int	num_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			else
				j++;
		}
		i++;
	}
	return (1);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_args(char **argv, t_monitor *m)
{
	if (!num_input)
	{
		error("enter only non-alphabetic arguments");
		return (0);
	}
	m->num_of_philos = ft_atol(argv[1]);
	m->die = ft_atol(argv[2]);
	m->time_of_eating = ft_atol(argv[3]);
	m->sleep = ft_atol(argv[4]);
	if (argv[5])
		m->meals = ft_atol(argv[5]);
	if (m->num_of_philos <= 0 || m->time_of_eating <= 0 || m->die <= 0 || m->sleep <= 0)
	{
		error("enter correct values (bigger than 0)");
		return (0);
	}
	if (m->num_of_philos > INT_MAX || m->time_of_eating > INT_MAX || m->die > INT_MAX || m->sleep > INT_MAX)
	{
		error("enter values smaller than INT_MAX only");
		return (0);
	}
}
