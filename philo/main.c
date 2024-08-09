/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:14:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/09 23:06:05 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

// bool	end_simulation()
// {
	// if death_flag

// }

int	start_simulation(t_monitor *m, t_philo **philos)
{

	m->beginning = get_ms();

	if (m->num_of_philos == 1)
		single_philo_routine(m, *philos);
	
	return (1);

}
	/*
	start of simulation timestamp?
	int i = 0;

	timestamp(m->start_of_sim);

	if (num_of_philos == 1)
		single_philo_routine();

	while (i < m->num_of_philos)
	{
		routine(m, philo[i]);
		i++;
	}
	start every philo thread
	and monitor thread
	*/

int	init_philosophers(t_monitor *monitor, t_philo *philo)
{
	int	i;
	t_forks	*forks;

	i = 0;
	forks = (t_forks *)malloc(sizeof(t_forks) * monitor->num_of_philos);
	if (!forks)
	{
		error("couldn't malloc() forks\n");
		return (0);
	}
	while (i < monitor->num_of_philos)
	{
		philo_info_dump(monitor, &philo[i], i, &forks);
		fork_info_dump(&forks[i], i);
		i++;
	}
	return (1);
}

static int	init_monitor(t_monitor *m, char **argv)
{
	m->meal_counter = false;
	m->end_flag = false;
	m->array_of_philos = (t_philo *)malloc(sizeof(t_philo) * m->num_of_philos);
	if (!m->array_of_philos)
	{
		error("couldn't malloc() philos\n");
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
		printf("first check ok\n");
		if (!init_monitor(&monitor, argv))
			return (2);
		printf("second check ok\n");
		if (!init_philosophers(&monitor, monitor.array_of_philos))
			return (3);
		printf("third ok\n");
		if (!start_simulation(&monitor, &monitor.array_of_philos))
			return (4);
		// clean up -> destroy locks and stack memory
	}
	return (0);

}
