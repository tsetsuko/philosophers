/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:14:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/08 18:22:06 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

bool	end_simulation()
{

}

int	start_simulation()
{


}

static int	init_philosophers(t_monitor monitor, t_philo **philo)
{
	int	i;
	t_forks	*forks;

	i = 0;
	forks = (t_forks *)malloc(sizeof(t_forks) * monitor.num_of_philos);
	if (!forks)
	{
		error("couldn't malloc() forks\n");
		return (0);
	}
	while (i < monitor.num_of_philos)
	{
		philo_info_dump(monitor, philo[i], i, &forks);
		fork_info_dump(&forks[i], i);
		i++;
	}
	return (1);
}

static int	init_monitor(t_monitor *m, char **argv)
{
	m->meal_counter = false;
	m->array_of_philos = malloc(sizeof(t_philo) * m->num_of_philos);
	if (!m->array_of_philos)
	{
		error("couldn't malloc() monitor\n");
		return (0);
	}
	if (argv[5])
		m->meal_counter = true;
	return (1);
}
int main(int argc, char **argv)
{
	t_monitor monitor;

	if (argc == 5 || argc == 6)
	{
		// 🧾 🧾 check if the arguments are all non-alpha
		if (!check_args(argv, &monitor))
			return (1);
		if (!init_monitor(&monitor, argv))
			return (2);
		if (!init_philosophers(monitor, monitor.array_of_philos))
			return (3);
		// START SIMULATION 
		if (!start_simulation())
			return (4);
	}
	return (0);

}
