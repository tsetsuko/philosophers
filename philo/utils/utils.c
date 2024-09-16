/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:18:29 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/16 14:35:00 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '-' || c == '+')
		return (1);
	return (0);
}

int	check_args(char **argv, t_monitor *m, int argc)
{
	if (argc != 5 && argc != 6)
		return (error("enter correct number of arguments"));
	if (!num_input(argv))
		return (error("enter only non-alphabetic arguments"));
	m->num_of_philos = ft_atol(argv[1]);
	m->die = ft_atol(argv[2]);
	m->time_of_eating = ft_atol(argv[3]);
	m->sleep = ft_atol(argv[4]);
	if (argv[5])
		m->meals = ft_atol(argv[5]);
	if (m->num_of_philos <= 0 || m->time_of_eating <= 0 || m->die <= 0 || m->sleep <= 0)
		return (error("enter correct values (bigger than 0)"));
	if (m->num_of_philos > INT_MAX || m->time_of_eating > INT_MAX || m->die > INT_MAX || m->sleep > INT_MAX)
		return (error("enter values smaller than INT_MAX only"));
	return (1);
}
