/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:14:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/07/28 20:21:41 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"


init_monitor(t_monitor monitor, char **argv)
{
	monitor.num_of_philos = ft_atoi(argv[1]);
	monitor.time_of_eating = ft_atoi(argv[3]);
	monitor.die = ft_atoi(argv[2]);
	if (argv[5])
		monitor.meals = ft_atoi(argv[5]);
	monitor.sleep = ft_atoi(argv[4]);
}
int main(int argc, char **argv)
{
	t_monitor monitor;
	if (argc == 5)
	{
		// all args must be numbers
		check_args();
		init_monitor(monitor, argv);
	}

}
