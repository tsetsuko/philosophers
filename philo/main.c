/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:18:56 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/07/27 16:30:48 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

parsing(t_monitor monitor, char **argv)
{
	monitor.num_of_philos = ft_atoi(argv[1]);
	monitor.die = ft_atoi(argv[2]);
	monitor.eat = ft_atoi(argv[3]);
}
int	main(int argc, char **argv)
{
	t_monitor	monitor;
	
	printf("%d\n", argc);
	if (argc != 5 && argc != 6)
		error(MAGENTA"there should be 5 or 6 arguments\n");
	else
	{
		if (!check_args(argv))
			error("don't enter non-numeric arguments\n");
		parsing(monitor, argv);
	}
}
